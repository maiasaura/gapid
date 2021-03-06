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

package log

import (
	"github.com/google/gapid/core/fault/severity"
	"github.com/google/gapid/core/text/note"
)

// Testing returns a default context with a TestHandler installed.
func Testing(t delegate) Context {
	ctx := Background().
		PreFilter(NoLimit).
		Filter(Pass)
	if t == nil {
		stdout := Stdout(Normal)
		return ctx.Handler(func(page note.Page) error {
			err := stdout(page)
			if level := severity.FindLevel(page); level <= severity.Critical {
				panic(level)
			}
			return err
		})
	}
	return ctx.Handler(TestHandler(Normal, t))
}

// TestHandler is a Handler that uses the style to write records to t's log methods
func TestHandler(style note.Style, t delegate) note.Handler {
	return func(page note.Page) error {
		level := severity.FindLevel(page)
		switch {
		case level <= severity.Critical:
			t.Fatal(style.Print(page))
		case level <= severity.Error:
			t.Error(style.Print(page))
		default:
			t.Log(style.Print(page))
		}
		return nil
	}
}

// delegate matches the logging methods of the test host types.
type delegate interface {
	Fatal(...interface{})
	Error(...interface{})
	Log(...interface{})
}
