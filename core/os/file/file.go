// Copyright (C) 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package file

import (
	"io"
	"os"

	"github.com/google/gapid/core/fault/cause"
	"github.com/google/gapid/core/log"
)

// Mkdir creates the directory specified.
func Mkdir(dir Path) error {
	if dir.IsEmpty() {
		return nil
	}
	return os.MkdirAll(dir.value, os.ModePerm)
}

// Remove deletes the file at f.
func Remove(f Path) error {
	return os.Remove(f.value)
}

// RemoveAll deletes the path and all chidren rooted at f.
func RemoveAll(f Path) error {
	return os.RemoveAll(f.value)
}

// Symlink creates a new symbolic-link at link to target.
func Symlink(link, target Path) error {
	return os.Symlink(target.value, link.value)
}

// Link creates a new hard-link at link to target.
func Link(link, target Path) error {
	return os.Link(target.value, link.value)
}

// Relink repoints link to target using the provided linking function.
func Relink(link, target Path, method func(link, target Path) error) error {
	if link.Exists() {
		if err := Remove(link); err != nil {
			return err
		}
	}
	return method(link, target)
}

// Move moves the file at src to dst.
func Move(dst, src Path) error {
	Mkdir(src.Parent())
	return os.Rename(src.value, dst.value)
}

// Copy copies src to dst, replacing any existing file at dst.
func Copy(ctx log.Context, dst Path, src Path) error {
	ctx = ctx.V("Source", src).V("Destination", dst)
	s, err := os.Open(src.value)
	if err != nil {
		return cause.Explain(ctx, err, "Opening source")
	}
	defer s.Close()
	d, err := os.OpenFile(dst.System(), os.O_CREATE|os.O_TRUNC|os.O_WRONLY, src.Info().Mode())
	if err != nil {
		return cause.Explain(ctx, err, "Creating destination")
	}
	defer d.Close()
	if _, err = io.Copy(d, s); err != nil {
		return cause.Explain(ctx, err, "Copying data")
	}
	return nil
}
