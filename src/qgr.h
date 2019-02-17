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
	class QgrApi {
	 public:
		virtual qgr::js::Worker* create_worker(
			Environment* env, bool is_inspector,int argc, const char* const* arg) = 0;
		virtual void delete_worker(qgr::js::Worker* worker) = 0;
		virtual void run_loop() = 0;
		virtual char* encoding_to_utf8(const uint16_t* src, int length, int* out_len) = 0;
		virtual uint16_t* decoding_utf8_to_uint16(const char* src, int length, int* out_len) = 0;
		virtual void print(const char* msg, ...) = 0;
		virtual bool is_process_exit() = 0;
	};

	extern QgrApi* qgr_api;
	extern void set_qgr_api(QgrApi* api);

	class QgrEnvironment {
	 public:
		QgrEnvironment(Environment* env, bool is_inspector, int argc, const char* const* argv);
		~QgrEnvironment();
	 private:
		qgr::js::Worker* m_worker;
	};
}

#endif
