#include <node.h>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::String;
using v8::Value;
using v8::Array;
using namespace node;


void max(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
	if (!args[0]->IsArray()) {
		isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "the first argument shoud be []")));
		return;
	}

	Local<Array> arr = Local<Array> ::Cast(args[0]);
	const uint32_t len = arr->Length();

	Local<Number> max = arr->Get(0)->ToNumber();
	for(uint32_t i = 0; i<len; i++){
		if (!arr->Get(i)->IsNumber()) {
			isolate->ThrowException(v8::Exception::TypeError(
				String::NewFromUtf8(isolate, "the array should only contain numbers")));
			return;
		}
		if (max->Value() < arr->Get(i)->ToNumber()->Value())
		{
			max = arr->Get(i)->ToNumber();			
		}
	}
	args.GetReturnValue().Set(max); 
 }

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "max", max);
}

NODE_MODULE(addon, init)

