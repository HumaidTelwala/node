// Copyright 2023 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/compiler/turboshaft/wasm-revec-phase.h"

#include "src/compiler/js-heap-broker.h"
#include "src/compiler/turboshaft/copying-phase.h"
#include "src/compiler/turboshaft/wasm-revec-reducer.h"

namespace v8::internal::compiler::turboshaft {

void WasmRevecPhase::Run(PipelineData* data, Zone* temp_zone) {
  WasmRevecAnalyzer analyzer(data, temp_zone, data->graph());

  if (analyzer.ShouldReduce()) {
    data->set_wasm_revec_analyzer(&analyzer);
    UnparkedScopeIfNeeded scope(data->broker(),
                                v8_flags.turboshaft_trace_reduction);
    CopyingPhase<WasmRevecReducer>::Run(data, temp_zone);
    data->clear_wasm_revec_analyzer();
  }
}

}  // namespace v8::internal::compiler::turboshaft
