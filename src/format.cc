#include <FLAC/format.h>
#include <nan.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_GETTER(FLAC__StreamMetadata_type) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->type));
}

NAN_GETTER(FLAC__StreamMetadata_is_last) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New<Boolean>(m->is_last));
}

NAN_GETTER(FLAC__StreamMetadata_length) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  info.GetReturnValue().Set(Nan::New(m->length));
}

template <>
void StructToJs(FLAC__StreamMetadata_Picture*, Local<Object>&);

template <>
void StructToJs(FLAC__StreamMetadata_StreamInfo*, Local<Object>&);

NAN_GETTER(FLAC__StreamMetadata_data) {
  FLAC__StreamMetadata* m = getPointer<FLAC__StreamMetadata>(info.This());
  Local<Object> obj = Nan::New<Object>();
  if (m->type == FLAC__METADATA_TYPE_STREAMINFO) {
    StructToJs(&m->data.stream_info, obj);
  } else if (m->type == FLAC__METADATA_TYPE_PICTURE) {
    StructToJs(&m->data.picture, obj);
  }
  info.GetReturnValue().Set(obj);
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_min_blocksize) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->min_blocksize));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_max_blocksize) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->max_blocksize));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_min_framesize) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->min_framesize));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_max_framesize) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->max_framesize));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_sample_rate) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->sample_rate));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_channels) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->channels));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_bits_per_sample) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->bits_per_sample));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_total_samples) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>((uint64_t)i->total_samples));
}

NAN_GETTER(FLAC__StreamMetadata_StreamInfo_md5sum) {
  FLAC__StreamMetadata_StreamInfo* i =
    getPointer<FLAC__StreamMetadata_StreamInfo>(info.This());
  Local<Array> md5sum = Nan::New<Array>(16);
  for (int j = 0; j < 16; j++) {
    Nan::Set(md5sum, j, Nan::New(i->md5sum[j]));
  }
  info.GetReturnValue().Set(md5sum);
}

NAN_GETTER(FLAC__StreamMetadata_Picture_type) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New((uint32_t)i->type));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_type) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  i->type =
      (FLAC__StreamMetadata_Picture_Type)Nan::To<uint32_t>(v.ToLocalChecked())
          .FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_mime_type) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New(i->mime_type).ToLocalChecked());
}

NAN_GETTER(FLAC__StreamMetadata_Picture_description) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New((char*)i->description).ToLocalChecked());
}

NAN_GETTER(FLAC__StreamMetadata_Picture_width) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New(i->width));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_width) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  i->width = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_height) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New(i->height));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_height) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  i->height = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_depth) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New(i->depth));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_depth) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  i->depth = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_colors) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(Nan::New(i->colors));
}

NAN_SETTER(FLAC__StreamMetadata_Picture_colors) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  MaybeLocal<Number> v = Nan::To<Number>(info.Data());
  if (v.IsEmpty()) {
    Nan::ThrowError("Invalid value: Has to be a Number");
  }
  i->colors = Nan::To<uint32_t>(v.ToLocalChecked()).FromJust();
}

NAN_GETTER(FLAC__StreamMetadata_Picture_data) {
  FLAC__StreamMetadata_Picture* i =
      getPointer<FLAC__StreamMetadata_Picture>(info.This());
  info.GetReturnValue().Set(WrapPtr(i->data, i->data_length).ToLocalChecked());
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

static Nan::Persistent<ObjectTemplate> StreamMetadata_StreamInfoTemplatePersistent;

template <>
void StructToJs(FLAC__StreamMetadata_StreamInfo* i, Local<Object>& obj) {
  if (StreamMetadata_StreamInfoTemplatePersistent.IsEmpty()) {
    Local<ObjectTemplate> otpl = Nan::New<ObjectTemplate>();
    Nan::SetAccessor(otpl, Nan::New("min_blocksize").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_min_blocksize);
    Nan::SetAccessor(otpl, Nan::New("max_blocksize").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_max_blocksize);
    Nan::SetAccessor(otpl, Nan::New("min_framesize").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_min_framesize);
    Nan::SetAccessor(otpl, Nan::New("max_framesize").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_max_framesize);
    Nan::SetAccessor(otpl, Nan::New("sample_rate").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_sample_rate);
    Nan::SetAccessor(otpl, Nan::New("channels").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_channels);
    Nan::SetAccessor(otpl, Nan::New("bits_per_sample").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_bits_per_sample);
    Nan::SetAccessor(otpl, Nan::New("total_samples").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_total_samples);
    Nan::SetAccessor(otpl, Nan::New("md5sum").ToLocalChecked(),
        FLAC__StreamMetadata_StreamInfo_md5sum);
    StreamMetadata_StreamInfoTemplatePersistent.Reset(otpl);
  }
  obj = Nan::NewInstance(Nan::New(StreamMetadata_StreamInfoTemplatePersistent))
            .ToLocalChecked();

  Local<Object> ptr = WrapPtr(i).ToLocalChecked();
  Nan::Set(obj, Nan::New("_ptr").ToLocalChecked(), ptr);
}

static Nan::Persistent<ObjectTemplate> StreamMetadata_PictureTemplatePersistent;

template <>
void StructToJs(FLAC__StreamMetadata_Picture* i, Local<Object>& obj) {
  if (StreamMetadata_PictureTemplatePersistent.IsEmpty()) {
    Local<ObjectTemplate> otpl = Nan::New<ObjectTemplate>();
    Nan::SetAccessor(otpl, Nan::New("type").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_type,
                     FLAC__StreamMetadata_Picture_type);
    Nan::SetAccessor(otpl, Nan::New("mime_type").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_mime_type);
    Nan::SetAccessor(otpl, Nan::New("description").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_description);
    Nan::SetAccessor(otpl, Nan::New("width").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_width,
                     FLAC__StreamMetadata_Picture_width);
    Nan::SetAccessor(otpl, Nan::New("height").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_height,
                     FLAC__StreamMetadata_Picture_height);
    Nan::SetAccessor(otpl, Nan::New("depth").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_depth,
                     FLAC__StreamMetadata_Picture_depth);
    Nan::SetAccessor(otpl, Nan::New("colors").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_colors,
                     FLAC__StreamMetadata_Picture_colors);
    Nan::SetAccessor(otpl, Nan::New("data").ToLocalChecked(),
                     FLAC__StreamMetadata_Picture_data);
    StreamMetadata_PictureTemplatePersistent.Reset(otpl);
  }
  obj = Nan::NewInstance(Nan::New(StreamMetadata_PictureTemplatePersistent))
            .ToLocalChecked();

  Local<Object> ptr = WrapPtr(i).ToLocalChecked();
  Nan::Set(obj, Nan::New("_ptr").ToLocalChecked(), ptr);
}

static Nan::Persistent<ObjectTemplate> StreamMetadataTemplatePersistent;

template <>
void StructToJs(FLAC__StreamMetadata* i, Local<Object>& obj) {
  if (StreamMetadataTemplatePersistent.IsEmpty()) {
    Local<ObjectTemplate> otpl = Nan::New<ObjectTemplate>();
    Nan::SetAccessor(otpl, Nan::New("type").ToLocalChecked(),
                     FLAC__StreamMetadata_type);
    Nan::SetAccessor(otpl, Nan::New("is_last").ToLocalChecked(),
                     FLAC__StreamMetadata_is_last);
    Nan::SetAccessor(otpl, Nan::New("length").ToLocalChecked(),
                     FLAC__StreamMetadata_length);
    Nan::SetAccessor(otpl, Nan::New("data").ToLocalChecked(),
                     FLAC__StreamMetadata_data);
    StreamMetadataTemplatePersistent.Reset(otpl);
  }
  obj = Nan::NewInstance(Nan::New(StreamMetadataTemplatePersistent))
            .ToLocalChecked();

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
