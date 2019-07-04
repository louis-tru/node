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
#include "langou.h"

typedef struct x509_store_st X509_STORE;

namespace langou {
	void set_ssl_root_x509_store_function(X509_STORE* (*)());
	namespace js {
		Worker* createWorkerWithNode(void* isolate, void* context);
	}
}

namespace node {

	namespace crypto {
		X509_STORE* NewRootCertStore();
	}

	LangouEnvironment::LangouEnvironment(Environment* env)
	{
		assert(!langou_env);
		langou_env = this;
		m_env = env;
		langou::set_ssl_root_x509_store_function(crypto::NewRootCertStore);
		v8::HandleScope scope(env->isolate());
		v8::Local<v8::Context> context = env->context();
		m_worker = langou::js::createWorkerWithNode(env->isolate(), &context);
	}

	class NodeApiIMPL: public NodeAPI {
	 public:

		int Start(int argc, char *argv[]) {
			return node::Start(argc, argv);
		}

		void* binding_node_module(const char* name) {
			assert(langou_env);
			auto env = langou_env->env();
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

	NODE_EXPORT int force_link_node() { /* noop */ return 0; }

}

NODE_C_CTOR(NodeApiIMPL_initialize) {
	assert(node::langou_node_api == nullptr);
	node::langou_node_api = new node::NodeApiIMPL();
}