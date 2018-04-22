#include <nan.h>
#include "dl.h"

using namespace v8;
using namespace node;

NAN_MODULE_INIT(init_metadata_lv1);

bool isLibFlacLoaded = false;
Library* libFlac;
Nan::Persistent<Object> module;

static void atExit(void*) {
  if (isLibFlacLoaded) {
    delete libFlac;
  }
}

NAN_METHOD(loadLibFlac) {
  if (info[0]->IsUndefined()) {
    Nan::ThrowError("Needs the path to the flac library");
  } else if (!info[0]->IsString()) {
    Nan::ThrowError("String needed representing the path to flac library");
  } else {
    Nan::Utf8String path(info[0]);
    libFlac = Library::load(*path);
    if (libFlac == nullptr) {
      Nan::ThrowError("Could not load library: check path");
    } else {
      isLibFlacLoaded = true;
      Handle<Object> obj = Nan::New(module);
      init_metadata_lv1(obj);
      Nan::Delete(obj, Nan::New("load").ToLocalChecked());
      info.GetReturnValue().Set(obj);
      AtExit(atExit);
    }
  }
}

NAN_MODULE_INIT(init) {
  module.Reset(target);
  libFlac = Library::load("libFLAC");
  if (libFlac == nullptr) {
#ifdef __linux__
    libFlac = Library::load("libFLAC", "so.8");
    if (libFlac == nullptr) {
#endif
      isLibFlacLoaded = false;
      Nan::Set(target, Nan::New("load").ToLocalChecked(), 
          Nan::GetFunction(Nan::New<FunctionTemplate>(loadLibFlac)).ToLocalChecked());
#ifdef __linux__
    }
#endif
  }

  isLibFlacLoaded = true;

  init_metadata_lv1(target);
  AtExit(atExit);
}

NODE_MODULE(binding, init);
