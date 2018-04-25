#include <nan.h>
#include <FLAC/metadata.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_METHOD(NODE_FLAC__metadata_object_new) {
  FLAC__MetadataType type = (FLAC__MetadataType) Nan::To<int>(info[0]).FromJust();
  FLAC__StreamMetadata* m = FLAC__metadata_object_new(type);
  if (m == nullptr) {
    info.GetReturnValue().SetNull();
  } else {
    info.GetReturnValue().Set(StructToJs(m));
  }
}

NAN_METHOD(NODE_FLAC__metadata_object_delete) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m != nullptr) FLAC__metadata_object_delete(m);
}

NAN_METHOD(NODE_FLAC__metadata_object_picture_set_mime_type) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  Nan::Utf8String mime_type(info[1]);
  FLAC__bool ret = FLAC__metadata_object_picture_set_mime_type(m, *mime_type, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(NODE_FLAC__metadata_object_picture_set_description) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  Nan::Utf8String description(info[1]);
  FLAC__bool ret = FLAC__metadata_object_picture_set_description(m, (FLAC__byte*) *description, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_object_picture_set_data) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if(m == nullptr) return;
  FLAC__byte* n = UnwrapPtr<FLAC__byte>(info[1]);
  uint32_t o = uint32_t(Buffer::Length(info[1]));
  FLAC__bool r = FLAC__metadata_object_picture_set_data(m, n, o, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_object_picture_is_legal) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if(m == nullptr) return;
  const char* n;
  FLAC__bool r = FLAC__metadata_object_picture_is_legal(m, &n);
  if(!r) {
    info.GetReturnValue().Set(Nan::New(n).ToLocalChecked());
  } else {
    info.GetReturnValue().Set(Nan::New<Boolean>(r));
  }
}

NAN_MODULE_INIT(init_metadata_object) {
  Local<Object> obj = Nan::New<Object>();

  Nan::SetMethod(obj, "new", NODE_FLAC__metadata_object_new);
  Nan::SetMethod(obj, "delete", NODE_FLAC__metadata_object_delete);
  Nan::SetMethod(obj, "picture_set_mime_type", NODE_FLAC__metadata_object_picture_set_mime_type);
  Nan::SetMethod(obj, "picture_set_description", NODE_FLAC__metadata_object_picture_set_description);
  Nan::SetMethod(obj, "picture_set_data", NODE_FLAC__metadata_object_picture_set_data);
  Nan::SetMethod(obj, "picture_is_legal", NODE_FLAC__metadata_object_picture_is_legal);

  Nan::Set(target, Nan::New("metadata_object").ToLocalChecked(), obj);
}
