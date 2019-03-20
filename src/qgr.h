/* ***** BEGIN LICENSE BLOCK *****
 * Distributed under the BSD license:
 *
 * Copyright (c) 2015, xuewen.chu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of xuewen.chu nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL xuewen.chu BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __qgr__node__
#define __qgr__node__

namespace qgr {
	namespace js {
		class Worker;
	}
}

namespace node {

	class Environment;

	class QgrEnvironment {
	 public:
		QgrEnvironment(Environment* env);
		~QgrEnvironment();
		inline qgr::js::Worker* worker() { return m_worker; }
		inline Environment* env() { return m_env; }
		void run_loop();
		char* encoding_to_utf8(const uint16_t* src, int length, int* out_len);
		uint16_t* decoding_utf8_to_uint16(const char* src, int length, int* out_len);
		bool is_exited();
	 private:
		qgr::js::Worker* m_worker;
		Environment* m_env;
	};

	class NodeAPI {
	 public:
		virtual int Start(int argc, char *argv[]) = 0;
		virtual void* binding_node_module(const char* name) = 0;
	};

	extern QgrEnvironment* qgr_env;
	extern NodeAPI* qgr_node_api;
}

#endif
