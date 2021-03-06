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

package scheduler

import (
	"github.com/google/gapid/core/log"
	"github.com/google/gapid/test/robot/build"
	"github.com/google/gapid/test/robot/job"
	"github.com/google/gapid/test/robot/monitor"
	"github.com/google/gapid/test/robot/replay"
)

func (s schedule) getReplayTargetTools(ctx log.Context) *build.ToolSet {
	ctx = ctx.V("Target", s.worker.Target)
	tools := s.pkg.FindTools(ctx, s.data.FindDevice(s.worker.Target))
	if tools == nil {
		return nil
	}
	if tools.Gapir == "" {
		return nil
	}
	return tools
}

func (s schedule) doReplay(ctx log.Context, t *monitor.Trace) error {
	if !s.worker.Supports(job.Replay) {
		return nil
	}
	ctx = ctx.Enter("Replay")
	ctx = ctx.V("Package", s.pkg.Id)
	hostTools := s.getHostTools(ctx)
	targetTools := s.getReplayTargetTools(ctx)
	if hostTools == nil || targetTools == nil {
		return nil
	}
	input := &replay.Input{
		Trace: t.Action.Output.Trace,
		Gapit: hostTools.Gapit,
		Gapis: hostTools.Gapis,
		Gapir: targetTools.Gapir,
	}
	action := &replay.Action{
		Input:  input,
		Host:   s.worker.Host,
		Target: s.worker.Target,
	}
	if _, found := s.data.Replays.FindOrCreate(ctx, action); found {
		return nil
	}
	// TODO: we just ignore the error right now, what should we do?
	go s.managers.Replay.Do(ctx, action.Target, input)
	return nil
}
