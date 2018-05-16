#include <FLAC/metadata.h>
#include <nan.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_PROPERTY_GETTER(SimpleIteratorStatus) {
  Nan::Utf8String p(property);
  std::string PropertyName(*p);
  for (int i = 0; i < 13; i++) {
    if (PropertyName == FLAC__Metadata_SimpleIteratorStatusString[i]) {
      info.GetReturnValue().Set(Nan::New(i));
      return;
    }
  }
  info.GetReturnValue().SetUndefined();
}

NAN_PROPERTY_ENUMERATOR(SimpleIteratorStatus) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 13; i++) {
    Nan::Set(arr, i,
             Nan::New(FLAC__Metadata_SimpleIteratorStatusString[i])
                 .ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_INDEX_GETTER(SimpleIteratorStatusString) {
  if (index < 13) {
    info.GetReturnValue().Set(
        Nan::New(FLAC__Metadata_SimpleIteratorStatusString[index])
            .ToLocalChecked());
  } else {
    info.GetReturnValue().SetUndefined();
  }
}

NAN_INDEX_ENUMERATOR(SimpleIteratorStatusString) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 13; i++) Nan::Set(arr, i, Nan::New(i));
  info.GetReturnValue().Set(arr);
}

NAN_MODULE_INIT(init_metadata) {
  Local<Object> obj = Nan::New<Object>();


  Local<ObjectTemplate> SimpleIteratorStatusTemplate =
      Nan::New<ObjectTemplate>();
  SetNamedPropertyHandlerFix(SimpleIteratorStatusTemplate, SimpleIteratorStatus,
                             nullptr, nullptr, nullptr, SimpleIteratorStatus);
  Nan::Set(obj, Nan::New("SimpleIteratorStatus").ToLocalChecked(),
           Nan::NewInstance(SimpleIteratorStatusTemplate).ToLocalChecked());

  Local<ObjectTemplate> SimpleIteratorStatusStringTemplate =
      Nan::New<ObjectTemplate>();
  Nan::SetIndexedPropertyHandler(SimpleIteratorStatusStringTemplate,
                                 SimpleIteratorStatusString, nullptr, nullptr,
                                 nullptr, SimpleIteratorStatusString);
  Nan::Set(
      obj, Nan::New("SimpleIteratorStatusString").ToLocalChecked(),
      Nan::NewInstance(SimpleIteratorStatusStringTemplate).ToLocalChecked());

  Nan::Set(target, Nan::New("metadata").ToLocalChecked(), obj);
}
