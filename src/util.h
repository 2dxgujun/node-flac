#ifndef FLAC_BINDINGS__UTIL_H
#define FLAC_BINDINGS__UTIL_H

#include <nan.h>

inline static Nan::MaybeLocal<v8::Object> WrapPointer(void* ptr, size_t length = 0) {
  return Nan::NewBuffer((char*) (void*) ptr, length);
}

inline static void* UnwrapPointer(v8::Handle<v8::Value> buffer) {
  void* ptr = nullptr;
  if (node::Buffer::HasInstance(buffer)) {
    ptr = node::Buffer::Data(buffer.As<v8::Object>());
  }
  return reinterpret_cast<void*>(ptr);
}

template<typename T> void structToJs(const T* i, Local<Object> &obj);
template<typename T> Local<Object> structToJs(const T* i) {
  Nan::EscapableHandleScope scope;
  Local<Object> obj = Nan::New<Object>();
  structToJs(i, obj);
  return scope.Escape(obj);
}
template<typename T> static T* fromjs(const Local<Value> &m) {
  Nan::HandleScope scope;
  if(!m->IsObject()) { Nan::ThrowError(Nan::Error("Only objects accepted in metadata APIs")); return nullptr; }
  MaybeLocal<Value> ptr = Nan::Get(Nan::To<Object>(m).ToLocalChecked(), Nan::New("_ptr").ToLocalChecked());
  if(ptr.IsEmpty()) { Nan::ThrowError(Nan::Error("This object was not created by the FLAC API")); return nullptr; }
  if(!m->IsObject()) { Nan::ThrowError(Nan::Error("This object was not created by the API or was modified incorrecty")); return nullptr; }
  Local<Value> ptr2 = ptr.ToLocalChecked();
  if(!Buffer::HasInstance(ptr2)) { Nan::ThrowError(Nan::Error("This object was modified incorrectly")); return nullptr; }
  return UnwrapPointer<T>(ptr2);
}

#endif
