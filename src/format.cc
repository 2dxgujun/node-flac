#include <FLAC/format.h>
#include <nan.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_GETTER(FLAC__StreamMetadata_type) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->type));
}

NAN_GETTER(FLAC__StreamMetadata_isLast) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New<Boolean>(m->is_last));
}

NAN_GETTER(FLAC__StreamMetadata_length) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->length));
}

NAN_GETTER(FLAC__StreamMetadata_Picture_type) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)m->data.picture.type));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_type) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  m->data.picture.type =
      (FLAC__StreamMetadata_Picture_Type)Nan::To<uint32_t>(v.ToLocalChecked())
          .FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_mime_type) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(
      Nan::New(m->data.picture.mime_type).ToLocalChecked());
}

NAN_GETTER(FLAC__StreamMetadata_Picture_description) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(
      Nan::New((char*)m->data.picture.description).ToLocalChecked());
}

NAN_GETTER(FLAC__StreamMetadata_Picture_width) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->data.picture.width));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_width) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  m->data.picture.width = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_height) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->data.picture.height));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_height) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  m->data.picture.height = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_depth) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->data.picture.depth));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_depth) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  m->data.picture.depth = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_colors) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->data.picture.colors));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_colors) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  m->data.picture.colors = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_data) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(
      WrapPtr(m->data.picture.data, m->data.picture.data_length)
          .ToLocalChecked());
}

NAN_PROPERTY_GETTER(MetadataType) {
  Nan::Utf8String p(property);
  std::string PropertyName(*p);
  for (int i = 0; i < 7; i++) {
    if (PropertyName == FLAC__MetadataTypeString[i]) {
      info.GetReturnValue().Set(Nan::New(i));
      return;
    }
  }
  info.GetReturnValue().SetUndefined();
}

NAN_PROPERTY_ENUMERATOR(MetadataType) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 7; i++) {
    Nan::Set(arr, i, Nan::New(FLAC__MetadataTypeString[i]).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_INDEX_GETTER(MetadataTypeString) {
  if (index < 7) {
    info.GetReturnValue().Set(
        Nan::New(FLAC__MetadataTypeString[index]).ToLocalChecked());
  } else {
    info.GetReturnValue().SetNull();
  }
}

NAN_INDEX_ENUMERATOR(MetadataTypeString) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 7; i++) {
    Nan::Set(arr, i, Nan::New(i));
  }
  info.GetReturnValue().Set(arr);
}

NAN_PROPERTY_GETTER(StreamMetadata_Picture_Type) {
  Nan::Utf8String p(property);
  std::string PropertyName(*p);
  for (int i = 0; i < 21; i++) {
    if (PropertyName == FLAC__StreamMetadata_Picture_TypeString[i]) {
      info.GetReturnValue().Set(Nan::New(i));
      return;
    }
  }
  info.GetReturnValue().SetUndefined();
}

NAN_PROPERTY_ENUMERATOR(StreamMetadata_Picture_Type) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 21; i++) {
    Nan::Set(
        arr, i,
        Nan::New(FLAC__StreamMetadata_Picture_TypeString[i]).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_INDEX_GETTER(StreamMetadata_Picture_TypeString) {
  if (index < 21) {
    info.GetReturnValue().Set(
        Nan::New(FLAC__StreamMetadata_Picture_TypeString[index])
            .ToLocalChecked());
  } else {
    info.GetReturnValue().SetNull();
  }
}

NAN_INDEX_ENUMERATOR(StreamMetadata_Picture_TypeString) {
  Local<Array> arr = Nan::New<Array>();
  for (int i = 0; i < 21; i++) {
    Nan::Set(arr, i, Nan::New(i));
  }
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(__FLAC__format_picture_is_legal) {
  FLAC__StreamMetadata_Picture* picture =
      fromjs<FLAC__StreamMetadata_Picture>(info[0]);
  const char* violation = nullptr;
  FLAC__bool ret = FLAC__format_picture_is_legal(picture, &violation);
  if (ret) {
    info.GetReturnValue().Set(Nan::New<Boolean>(ret));
  } else {
    info.GetReturnValue().Set(Nan::New(violation).ToLocalChecked());
  }
}

NAN_ASYNC_METHOD(__FLAC__format_picture_is_legal) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata_Picture* picture =
      fromjs<FLAC__StreamMetadata_Picture>(info[0]);
  const char* violation = nullptr;
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__StreamMetadata_Picture*, const char*>(
          cb,
          [](BindingWorker<void, FLAC__StreamMetadata_Picture*, const char*>*
                 worker,
             FLAC__StreamMetadata_Picture* picture, const char* violation) {
            if (!FLAC__format_picture_is_legal(picture, &violation)) {
              worker->SetErrorMessage(violation);
            }
          },
          picture, violation));
}

template <>
Local<Value> StructToJs(off_t i) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::New<Number>(i));
}

template <>
Local<Value> StructToJs(unsigned i) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::New<Number>(i));
}

template <>
Local<Value> StructToJs(FLAC__MetadataType i) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::New<Number>(i));
}

template <>
Local<Value> StructToJs(FLAC__bool i) {
  Nan::EscapableHandleScope scope;
  if (i) {
    return scope.Escape(Nan::True());
  } else {
    return scope.Escape(Nan::False());
  }
}

template <>
void StructToJs(FLAC__StreamMetadata_Picture* i, Local<Object>& obj) {
  Nan::SetAccessor(obj, Nan::New("type").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_type,
                   FLAC__StreamMetadata_Picture_type);
  Nan::SetAccessor(obj, Nan::New("mime_type").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_mime_type);
  Nan::SetAccessor(obj, Nan::New("description").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_description);
  Nan::SetAccessor(obj, Nan::New("width").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_width,
                   FLAC__StreamMetadata_Picture_width);
  Nan::SetAccessor(obj, Nan::New("height").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_height,
                   FLAC__StreamMetadata_Picture_height);
  Nan::SetAccessor(obj, Nan::New("depth").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_depth,
                   FLAC__StreamMetadata_Picture_depth);
  Nan::SetAccessor(obj, Nan::New("colors").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_colors,
                   FLAC__StreamMetadata_Picture_colors);
  Nan::SetAccessor(obj, Nan::New("data").ToLocalChecked(),
                   FLAC__StreamMetadata_Picture_data);
}

template <>
void StructToJs(FLAC__StreamMetadata* i, Local<Object>& obj) {
  if (i->type == FLAC__METADATA_TYPE_PICTURE) {
    StructToJs(&i->data.picture, obj);
  }

  Nan::SetAccessor(obj, Nan::New("type").ToLocalChecked(),
                   FLAC__StreamMetadata_type);
  Nan::SetAccessor(obj, Nan::New("isLast").ToLocalChecked(),
                   FLAC__StreamMetadata_isLast);
  Nan::SetAccessor(obj, Nan::New("length").ToLocalChecked(),
                   FLAC__StreamMetadata_length);

  Local<Object> ptr = Nan::NewBuffer((char*)i, 0,
                                     [](char* i, void* data) {
                                       FLAC__metadata_object_delete(
                                           (FLAC__StreamMetadata*)data);
                                     },
                                     i)
                          .ToLocalChecked();

  Nan::Set(obj, Nan::New("_ptr").ToLocalChecked(), ptr);
}

NAN_MODULE_INIT(init_format) {
  Local<Object> obj = Nan::New<Object>();

  Nan::Set(obj, Nan::New("FLAC__VERSION_STRING").ToLocalChecked(),
           Nan::New<String>(FLAC__VERSION_STRING).ToLocalChecked());
  Nan::Set(obj, Nan::New("FLAC__VENDOR_STRING").ToLocalChecked(),
           Nan::New<String>(FLAC__VENDOR_STRING).ToLocalChecked());

  SET_METHOD(picture_is_legal, __FLAC__format_picture_is_legal)

  Local<ObjectTemplate> MetadataTypeTemplate = Nan::New<ObjectTemplate>();
  SetNamedPropertyHandlerFix(MetadataTypeTemplate, MetadataType, nullptr,
                             nullptr, nullptr, MetadataType);
  Nan::Set(obj, Nan::New("MetadataType").ToLocalChecked(),
           Nan::NewInstance(MetadataTypeTemplate).ToLocalChecked());

  Local<ObjectTemplate> MetadataTypeStringTemplate = Nan::New<ObjectTemplate>();
  Nan::SetIndexedPropertyHandler(MetadataTypeStringTemplate, MetadataTypeString,
                                 nullptr, nullptr, nullptr, MetadataTypeString);
  Nan::Set(obj, Nan::New("MetadataTypeString").ToLocalChecked(),
           Nan::NewInstance(MetadataTypeStringTemplate).ToLocalChecked());

  Local<ObjectTemplate> StreamMetadata_Picture_TypeTemplate =
      Nan::New<ObjectTemplate>();
  SetNamedPropertyHandlerFix(StreamMetadata_Picture_TypeTemplate,
                             StreamMetadata_Picture_Type, nullptr, nullptr,
                             nullptr, StreamMetadata_Picture_Type);
  Nan::Set(
      obj, Nan::New("StreamMetadata_Picture_Type").ToLocalChecked(),
      Nan::NewInstance(StreamMetadata_Picture_TypeTemplate).ToLocalChecked());

  Local<ObjectTemplate> StreamMetadata_Picture_TypeStringTemplate =
      Nan::New<ObjectTemplate>();
  Nan::SetIndexedPropertyHandler(StreamMetadata_Picture_TypeStringTemplate,
                                 StreamMetadata_Picture_TypeString, nullptr,
                                 nullptr, nullptr,
                                 StreamMetadata_Picture_TypeString);
  Nan::Set(obj, Nan::New("StreamMetadata_Picture_TypeString").ToLocalChecked(),
           Nan::NewInstance(StreamMetadata_Picture_TypeStringTemplate)
               .ToLocalChecked());

  Nan::Set(target, Nan::New("format").ToLocalChecked(), obj);
}
