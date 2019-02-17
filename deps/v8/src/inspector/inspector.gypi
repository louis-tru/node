# Copyright 2016 the V8 project authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'inspector_generated_sources': [
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Forward.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Protocol.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Protocol.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Console.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Console.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Debugger.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Debugger.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/HeapProfiler.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/HeapProfiler.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Profiler.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Profiler.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Runtime.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Runtime.h',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Schema.cpp',
      '<(SHARED_INTERMEDIATE_DIR)/src/inspector/protocol/Schema.h',
      '<(SHARED_INTERMEDIATE_DIR)/include/inspector/Debugger.h',
      '<(SHARED_INTERMEDIATE_DIR)/include/inspector/Runtime.h',
      '<(SHARED_INTERMEDIATE_DIR)/include/inspector/Schema.h',
    ],

    'inspector_injected_script_source': 'injected-script-source.js',
    'inspector_generated_injected_script': '<(SHARED_INTERMEDIATE_DIR)/src/inspector/injected-script-source.h',
    'inspector_debugger_script_source': 'debugger-script.js',
    'inspector_generated_debugger_script': '<(SHARED_INTERMEDIATE_DIR)/src/inspector/debugger-script.h',

    'inspector_all_sources': [
      '<@(inspector_generated_sources)',
      '<(inspector_generated_injected_script)',
      '<(inspector_generated_debugger_script)',
      #'../../include/v8-inspector.h',
      #'../../include/v8-inspector-protocol.h',
      'inspector/injected-script.cc',
      'inspector/injected-script.h',
      'inspector/inspected-context.cc',
      'inspector/inspected-context.h',
      'inspector/java-script-call-frame.cc',
      'inspector/java-script-call-frame.h',
      'inspector/remote-object-id.cc',
      'inspector/remote-object-id.h',
      'inspector/script-breakpoint.h',
      'inspector/search-util.cc',
      'inspector/search-util.h',
      'inspector/string-16.cc',
      'inspector/string-16.h',
      'inspector/string-util.cc',
      'inspector/string-util.h',
      'inspector/test-interface.cc',
      'inspector/test-interface.h',
      'inspector/v8-console.cc',
      'inspector/v8-console.h',
      'inspector/v8-console-agent-impl.cc',
      'inspector/v8-console-agent-impl.h',
      'inspector/v8-console-message.cc',
      'inspector/v8-console-message.h',
      'inspector/v8-debugger.cc',
      'inspector/v8-debugger.h',
      'inspector/v8-debugger-agent-impl.cc',
      'inspector/v8-debugger-agent-impl.h',
      'inspector/v8-debugger-script.cc',
      'inspector/v8-debugger-script.h',
      'inspector/v8-function-call.cc',
      'inspector/v8-function-call.h',
      'inspector/v8-heap-profiler-agent-impl.cc',
      'inspector/v8-heap-profiler-agent-impl.h',
      'inspector/v8-injected-script-host.cc',
      'inspector/v8-injected-script-host.h',
      'inspector/v8-inspector-impl.cc',
      'inspector/v8-inspector-impl.h',
      'inspector/v8-inspector-session-impl.cc',
      'inspector/v8-inspector-session-impl.h',
      'inspector/v8-internal-value-type.cc',
      'inspector/v8-internal-value-type.h',
      'inspector/v8-profiler-agent-impl.cc',
      'inspector/v8-profiler-agent-impl.h',
      'inspector/v8-regex.cc',
      'inspector/v8-regex.h',
      'inspector/v8-runtime-agent-impl.cc',
      'inspector/v8-runtime-agent-impl.h',
      'inspector/v8-schema-agent-impl.cc',
      'inspector/v8-schema-agent-impl.h',
      'inspector/v8-stack-trace-impl.cc',
      'inspector/v8-stack-trace-impl.h',
      'inspector/v8-value-copier.cc',
      'inspector/v8-value-copier.h',
      'inspector/wasm-translation.cc',
      'inspector/wasm-translation.h',
    ]
  }
}
