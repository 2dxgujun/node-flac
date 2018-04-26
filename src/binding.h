#ifndef FLAC_BINDINGS__BINDING_H_
#define FLAC_BINDINGS__BINDING_H_

#include <FLAC/metadata.h>
#include <nan.h>
#include <functional>

using namespace v8;
using namespace node;

inline void nop(char*, void*) { ; }

template <typename T = void>
inline Nan::MaybeLocal<Object> WrapPtr(T* ptr, size_t length = 0) {
  return Nan::NewBuffer((char*)(void*)ptr, length, nop, nullptr);
}

template <typename T = void>
inline T* UnwrapPtr(Local<Value> val) {
  void* ptr = nullptr;
  if (Buffer::HasInstance(val)) {
    ptr = Buffer::Data(val);
  }
  return reinterpret_cast<T*>(ptr);
}

template <typename T>
T* getPointer(const Local<Object>& thiz) {
  Nan::MaybeLocal<Value> _ptr =
      Nan::Get(thiz, Nan::New("_ptr").ToLocalChecked());
  if (_ptr.IsEmpty()) {
    Nan::ThrowError(Nan::Error("Object is not a Metadata object"));
  } else {
    Local<Value> val = _ptr.ToLocalChecked();
    if (!val->IsObject()) {
      Nan::ThrowError(
          Nan::Error("Corrupted Metadata object: Pointer is not an object"));
    } else {
      Local<Object> obj = val.As<Object>();
      if (!Buffer::HasInstance(obj)) {
        Nan::ThrowError(
            Nan::Error("Corrupted Metadata object: Pointer is invalid"));
      } else {
        return UnwrapPtr<T>(obj);
      }
    }
  }
  return nullptr;
}

template <typename T>
void StructToJs(const T* i, Local<Object>& obj);

template <typename T>
Local<Value> StructToJs(const T i) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::New(i));
}

template <>
inline Local<Value> StructToJs(const off_t i) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::New<Number>(i));
}

template <typename T>
Local<Object> StructToJs(const T* i) {
  Nan::EscapableHandleScope scope;
  Local<Object> obj = Nan::New<Object>();
  StructToJs(i, obj);
  return scope.Escape(obj);
}

template <typename T>
T* fromjs(const Local<Value>& m) {
  Nan::HandleScope scope;
  if (!m->IsObject()) {
    Nan::ThrowError(Nan::Error("Only objects accepted in metadata APIs"));
    return nullptr;
  }

  MaybeLocal<Value> ptr = Nan::Get(Nan::To<Object>(m).ToLocalChecked(),
                                   Nan::New("_ptr").ToLocalChecked());
  if (ptr.IsEmpty()) {
    Nan::ThrowError(Nan::Error("This object was not created by the API"));
    return nullptr;
  }

  Local<Value> ptr2 = ptr.ToLocalChecked();
  if (!ptr2->IsObject()) {
    Nan::ThrowError(Nan::Error(
        "This object was not create by the API or was modified incorrectly"));
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
                Ret (*func)(BindingWorker<Ret, Args...>* worker, Args...),
                Args... args)
      : Nan::AsyncWorker(callback),
        func([=]() { return func(this, args...); }) {}

  void Execute() { ret = func(); }

  void HandleOKCallback() {
    Nan::HandleScope scope;

    Local<Value> argv[] = {Nan::Undefined(), StructToJs(ret)};
    callback->Call(2, argv, async_resource);
  }

  void SetErrorMessage(const char* msg) {
    Nan::AsyncWorker::SetErrorMessage(msg);
  }

  private:
  Ret ret;
  std::function<Ret()> func;
};

template <typename... Args>
class BindingWorker<void, Args...> : public Nan::AsyncWorker {
  public:
  BindingWorker(Nan::Callback* callback,
                void (*func)(BindingWorker<void, Args...>* worker, Args...),
                Args... args)
      : Nan::AsyncWorker(callback), func([=]() { func(this, args...); }) {}

  void Execute() { func(); }

  void SetErrorMessage(const char* msg) {
    Nan::AsyncWorker::SetErrorMessage(msg);
  }

  private:
  std::function<void()> func;
};

// modified version of Nan::SetNamedPropertyHandler
// see https://github.com/nodejs/nan/issues/762
inline void SetNamedPropertyHandlerFix(
    Local<ObjectTemplate> tpl, Nan::PropertyGetterCallback getter,
    Nan::PropertySetterCallback setter = 0,
    Nan::PropertyQueryCallback query = 0,
    Nan::PropertyDeleterCallback deleter = 0,
    Nan::PropertyEnumeratorCallback enumerator = 0,
    Local<Value> data = Local<Value>()) {
  Nan::HandleScope scope;

  Nan::imp::NativePropertyGetter getter_ =
      Nan::imp::PropertyGetterCallbackWrapper;
  Nan::imp::NativePropertySetter setter_ =
      setter ? Nan::imp::PropertySetterCallbackWrapper : 0;
  Nan::imp::NativePropertyQuery query_ =
      query ? Nan::imp::PropertyQueryCallbackWrapper : 0;
  Nan::imp::NativePropertyDeleter* deleter_ =
      deleter ? Nan::imp::PropertyDeleterCallbackWrapper : 0;
  Nan::imp::NativePropertyEnumerator enumerator_ =
      enumerator ? Nan::imp::PropertyEnumeratorCallbackWrapper : 0;

  Local<ObjectTemplate> otpl = Nan::New<ObjectTemplate>();
  otpl->SetInternalFieldCount(Nan::imp::kPropertyFieldCount);
  Local<Object> obj = Nan::NewInstance(otpl).ToLocalChecked();
  obj->SetInternalField(Nan::imp::kPropertyGetterIndex,
                        Nan::New<External>(reinterpret_cast<void*>(getter)));

  if (setter) {
    obj->SetInternalField(Nan::imp::kPropertySetterIndex,
                          Nan::New<External>(reinterpret_cast<void*>(setter)));
  }

  if (query) {
    obj->SetInternalField(Nan::imp::kPropertyQueryIndex,
                          Nan::New<External>(reinterpret_cast<void*>(query)));
  }

  if (deleter) {
    obj->SetInternalField(Nan::imp::kPropertyDeleterIndex,
                          Nan::New<External>(reinterpret_cast<void*>(deleter)));
  }

  if (enumerator) {
    obj->SetInternalField(
        Nan::imp::kPropertyEnumeratorIndex,
        Nan::New<External>(reinterpret_cast<void*>(enumerator)));
  }

  if (!data.IsEmpty()) {
    obj->SetInternalField(Nan::imp::kDataIndex, data);
  }

#if NODE_MODULE_VERSION > NODE_0_12_MODULE_VERSION
  tpl->SetHandler(v8::NamedPropertyHandlerConfiguration(
      getter_, setter_, query_, deleter_, enumerator_, obj,
      PropertyHandlerFlags::kOnlyInterceptStrings));
#else
  tpl->SetNamedPropertyHandler(getter_, setter_, query_, deleter_, enumerator_,
                               obj);
#endif
}

#endif
