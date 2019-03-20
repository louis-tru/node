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

#include "v8.h"
#include "qgr/js/js-1.h"
#include "qgr.h"
#include "qgr/utils/loop.h"
#include "qgr/utils/codec.h"

namespace qgr {
	extern void set_ssl_root_x509_store_function(X509_STORE* (*)());
}

namespace node {

	namespace crypto {
		extern X509_STORE* NewRootCertStore();
	}

	QgrEnvironment* qgr_env = nullptr;
	
	QgrEnvironment::QgrEnvironment(Environment* node_env)
	{
		assert(!qgr_env);
		qgr_env = this;
		m_env = node_env;
		qgr::set_ssl_root_x509_store_function(crypto::NewRootCertStore);
		v8::HandleScope scope(node_env->isolate());
		v8::Local<v8::Context> context = node_env->context();
		m_worker = qgr::js::IMPL::createWithNode(node_env->isolate(), &context);
	}

	QgrEnvironment::~QgrEnvironment() {
		qgr::Release(m_worker);
		m_worker = nullptr;
		qgr_env = nullptr;
	}

	void QgrEnvironment::run_loop() {
		qgr::RunLoop::main_loop()->run();
	}

	char* QgrEnvironment::encoding_to_utf8(const uint16_t* src, int length, int* out_len) {
		auto buff = qgr::Codec::encoding(qgr::Encoding::UTF8, src, length);
		*out_len = buff.length();
		return buff.collapse();
	}

	uint16_t* QgrEnvironment::decoding_utf8_to_uint16(const char* src, int length, int* out_len) {
		auto buff = qgr::Codec::decoding_to_uint16(qgr::Encoding::UTF8, src, length);
		*out_len = buff.length();
		return buff.collapse();
	}

	bool QgrEnvironment::is_exited() {
		return qgr::is_exited();
	}

	class NodeApiIMPL: public NodeAPI {
	 public:

		int Start(int argc, char *argv[]) {
			return node::Start(argc, argv);
		}

		void* binding_node_module(const char* name) {
			assert(qgr_env);
			auto env = qgr_env->env();
			auto isolate = env->isolate();
			auto type = v8::NewStringType::kInternalized;
			auto binding = v8::String::NewFromOneByte(
				isolate, (const uint8_t*)"binding", type).ToLocalChecked();
			auto func = v8::Local<v8::Function>::Cast(
				env->process_object()->Get(env->context(), binding).ToLocalChecked());
			v8::Local<v8::Value> argv =
				v8::String::NewFromOneByte(isolate, (const uint8_t*)name, type).ToLocalChecked();
			auto r = func->Call(env->context(), v8::Undefined(isolate), 1, &argv);
			return *reinterpret_cast<void**>(&r);
		}
	};

}

NODE_C_CTOR(NodeApiIMPL_initialize) {
	assert(!node::qgr_node_api);
	node::qgr_node_api = new node::NodeApiIMPL();
}