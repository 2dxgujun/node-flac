#ifndef FLAC_BINDINGS__BINDING_H_
#define FLAC_BINDINGS__BINDING_H_

#include <nan.h>
#include <FLAC/metadata.h>

using namespace v8;
using namespace node;

inline void nop(char*,void*) {;}

template<typename T = void>
inline Nan::MaybeLocal<Object> WrapPtr(T* ptr, size_t length = 0) {
  return Nan::NewBuffer((char*) (void*) ptr, length, nop, nullptr);
}

template<typename T = void>
inline T* UnwrapPtr(Local<Value> val) {
  void* ptr = nullptr;
  if (Buffer::HasInstance(val)) {
    ptr = Buffer::Data(val);
  }
  return reinterpret_cast<T*>(ptr);
}

template<typename T>
T* getPointer(const Local<Object> &thiz) {
  Nan::MaybeLocal<Value> _ptr = Nan::Get(thiz, Nan::New("_ptr").ToLocalChecked());
  if (_ptr.IsEmpty()) {
    Nan::ThrowError(Nan::Error("Object is not a Metadata object"));
  } else {
    Local<Value> val = _ptr.ToLocalChecked();
    if (!val->IsObject()) {
      Nan::ThrowError(Nan::Error("Corrupted Metadata object: Pointer is not an object"));
    } else {
      Local<Object> obj = val.As<Object>();
      if (!Buffer::HasInstance(obj)) {
        Nan::ThrowError(Nan::Error("Corrupted Metadata object: Pointer is invalid"));
      } else {
        return UnwrapPtr<T>(obj);
      }
    }
  }
  return nullptr;
}

template<typename T> void StructToJs(const T* i, Local<Object> &obj);

template<typename T>
Local<Object> StructToJs(const T* i) {
  Nan::EscapableHandleScope scope;
  Local<Object> obj = Nan::New<Object>();
  StructToJs(i, obj);
  return scope.Escape(obj);
}


template<typename T>
T* fromjs(const Local<Value> &m) {
  Nan::HandleScope scope;
  if (!m->IsObject()) {
    Nan::ThrowError(Nan::Error("Only objects accepted in metadata APIs"));
    return nullptr;
  }

  MaybeLocal<Value> ptr = Nan::Get(Nan::To<Object>(m).ToLocalChecked(), Nan::New("_ptr").ToLocalChecked());
  if (ptr.IsEmpty()) {
    Nan::ThrowError(Nan::Error("This object was not created by the API"));
    return nullptr;
  }

  Local<Value> ptr2 = ptr.ToLocalChecked();
  if (!ptr2->IsObject()) {
    Nan::ThrowError(Nan::Error("This object was not create by the API or was modified incorrectly"));
    return nullptr;
  }
  if (!Buffer::HasInstance(ptr2)) {
    Nan::ThrowError(Nan::Error("This object was modified incorrectly"));
    return nullptr;
  }
  return UnwrapPtr<T>(ptr2);
}

template <typename Ret, typename... Args>
class BindingWorker : public Nan::AsyncWorker {
  public:
    BindingWorker(Nan::Callback* callback,
        Ret(*func)(BindingWorker<Ret, Args...>* worker, Args...),
        Args... args)
      : Nan::AsyncWorker(callback), func([=]() { return func(this, args...); }) {}
    ~BindingWorker() {}

    void Execute() {
      ret = func();
    }

    void HandleOKCallback() {
      Nan::HandleScope scope;
      Local<Value> argv[] = {
        Nan::Null(),
        StructToJs(ret)
      };

      callback->Call(2, argv, async_resource);
    }

  private:
    Ret ret;
    std::function<Ret()> func;
};

#endif
