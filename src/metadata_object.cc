#include <FLAC/metadata.h>
#include <nan.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_METHOD(__FLAC__metadata_object_new) {
  FLAC__MetadataType type =
      (FLAC__MetadataType)Nan::To<int>(info[0]).FromJust();
  FLAC__StreamMetadata* m = FLAC__metadata_object_new(type);
  if (m == nullptr) {
    info.GetReturnValue().SetNull();
  } else {
    info.GetReturnValue().Set(StructToJs(m));
  }
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_new) {
  NEW_CALLBACK(cb)
  FLAC__MetadataType type =
      (FLAC__MetadataType)Nan::To<int>(info[0]).FromJust();
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__StreamMetadata*, FLAC__MetadataType>(
          cb,
          [](BindingWorker<FLAC__StreamMetadata*, FLAC__MetadataType>* worker,
             FLAC__MetadataType type) {
            return FLAC__metadata_object_new(type);
          },
          type));
}

NAN_METHOD(__FLAC__metadata_object_delete) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m != nullptr) FLAC__metadata_object_delete(m);
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_delete) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__StreamMetadata*>(
      cb,
      [](BindingWorker<void, FLAC__StreamMetadata*>* worker,
         FLAC__StreamMetadata* m) { FLAC__metadata_object_delete(m); },
      m));
}

NAN_METHOD(__FLAC__metadata_object_picture_set_mime_type) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  Nan::Utf8String mime_type(info[1]);
  FLAC__bool ret =
      FLAC__metadata_object_picture_set_mime_type(m, *mime_type, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_picture_set_mime_type) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  Nan::Utf8String* mime_type = new Nan::Utf8String(info[1]);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__StreamMetadata*,
                                          Nan::Utf8String*>(
      cb,
      [](BindingWorker<void, FLAC__StreamMetadata*, Nan::Utf8String*>* worker,
         FLAC__StreamMetadata* m, Nan::Utf8String* mime_type) {
        if (!FLAC__metadata_object_picture_set_mime_type(m, **mime_type,
                                                         true)) {
          worker->SetErrorMessage("Failed set mime_type to metadata object");
        }
        delete mime_type;
      },
      m, mime_type));
}

NAN_METHOD(__FLAC__metadata_object_picture_set_description) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  Nan::Utf8String description(info[1]);
  FLAC__bool r = FLAC__metadata_object_picture_set_description(
      m, (FLAC__byte*)*description, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_picture_set_description) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  Nan::Utf8String* description = new Nan::Utf8String(info[1]);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__StreamMetadata*,
                                          Nan::Utf8String*>(
      cb,
      [](BindingWorker<void, FLAC__StreamMetadata*, Nan::Utf8String*>* worker,
         FLAC__StreamMetadata* m, Nan::Utf8String* description) {
        if (!FLAC__metadata_object_picture_set_description(
                m, (FLAC__byte*)**description, true)) {
          worker->SetErrorMessage("Failed set description to metadata object");
        }
        delete description;
      },
      m, description));
}

NAN_METHOD(__FLAC__metadata_object_picture_set_data) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  FLAC__byte* n = UnwrapPtr<FLAC__byte>(info[1]);
  uint32_t o = uint32_t(Buffer::Length(info[1]));
  FLAC__bool r = FLAC__metadata_object_picture_set_data(m, n, o, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_picture_set_data) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  FLAC__byte* data = UnwrapPtr<FLAC__byte>(info[1]);
  uint32_t length = uint32_t(Buffer::Length(info[1]));
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__StreamMetadata*, FLAC__byte*, uint32_t>(
          cb,
          [](BindingWorker<void, FLAC__StreamMetadata*, FLAC__byte*, uint32_t>*
                 worker,
             FLAC__StreamMetadata* m, FLAC__byte* data, uint32_t length) {
            if (!FLAC__metadata_object_picture_set_data(m, data, length,
                                                        true)) {
              worker->SetErrorMessage("Failed set data to metadata object");
            }
          },
          m, data, length));
}

NAN_METHOD(__FLAC__metadata_object_picture_is_legal) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  const char* n;
  FLAC__bool r = FLAC__metadata_object_picture_is_legal(m, &n);
  if (!r) {
    Nan::ThrowError(n);
  } else {
    info.GetReturnValue().Set(Nan::New<Boolean>(r));
  }
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_picture_is_legal) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* object = fromjs<FLAC__StreamMetadata>(info[0]);
  const char* violation = nullptr;
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__StreamMetadata*, const char*>(
          cb,
          [](BindingWorker<void, FLAC__StreamMetadata*, const char*>* worker,
             FLAC__StreamMetadata* object, const char* violation) {
            if (!FLAC__metadata_object_picture_is_legal(object, &violation)) {
              worker->SetErrorMessage(violation);
            }
          },
          object, violation));
}

NAN_METHOD(__FLAC__metadata_object_vorbiscomment_remove_entries_matching) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  Nan::Utf8String field_name(info[1]);
  int r = FLAC__metadata_object_vorbiscomment_remove_entries_matching(
      m, *field_name);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_ASYNC_METHOD(
    __FLAC__metadata_object_vorbiscomment_remove_entries_matching) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  Nan::Utf8String* field_name = new Nan::Utf8String(info[1]);
  Nan::AsyncQueueWorker(new BindingWorker<int, FLAC__StreamMetadata*,
                                          Nan::Utf8String*>(
      cb,
      [](BindingWorker<int, FLAC__StreamMetadata*, Nan::Utf8String*>* worker,
         FLAC__StreamMetadata* m, Nan::Utf8String* field_name) {
        int num = FLAC__metadata_object_vorbiscomment_remove_entries_matching(
            m, **field_name);
        delete field_name;
        return num;
      },
      m, field_name));
}

NAN_METHOD(__FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair) {
  Nan::Utf8String field_name(info[0]);
  Nan::Utf8String field_value(info[1]);
  FLAC__StreamMetadata_VorbisComment_Entry* entry =
      new FLAC__StreamMetadata_VorbisComment_Entry();
  FLAC__bool r = FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(
      entry, *field_name, *field_value);
  if (r) {
    info.GetReturnValue().Set(StructToJs(entry));
  } else {
    Nan::ThrowError("Failed to create entry from name value pair");
  }
}

NAN_ASYNC_METHOD(
    __FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair) {
  NEW_CALLBACK(cb)
  Nan::Utf8String* field_name = new Nan::Utf8String(info[0]);
  Nan::Utf8String* field_value = new Nan::Utf8String(info[1]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__StreamMetadata_VorbisComment_Entry*,
                        Nan::Utf8String*, Nan::Utf8String*>(
          cb,
          [](BindingWorker<FLAC__StreamMetadata_VorbisComment_Entry*,
                           Nan::Utf8String*, Nan::Utf8String*>* worker,
             Nan::Utf8String* field_name, Nan::Utf8String* field_value)
              -> FLAC__StreamMetadata_VorbisComment_Entry* {
            FLAC__StreamMetadata_VorbisComment_Entry* entry =
                new FLAC__StreamMetadata_VorbisComment_Entry();
            FLAC__bool r =
                FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(
                    entry, **field_name, **field_value);
            delete field_name;
            delete field_value;
            if (r) {
              return entry;
            } else {
              worker->SetErrorMessage(
                  "Failed to create entry from name value pair");
              return nullptr;
            }
          },
          field_name, field_value));
}

NAN_METHOD(__FLAC__metadata_object_vorbiscomment_append_comment) {
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  FLAC__StreamMetadata_VorbisComment_Entry* entry =
      fromjs<FLAC__StreamMetadata_VorbisComment_Entry>(info[1]);
  if (entry == nullptr) return;
  FLAC__bool r =
      FLAC__metadata_object_vorbiscomment_append_comment(m, *entry, true);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_object_vorbiscomment_append_comment) {
  NEW_CALLBACK(cb)
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[0]);
  if (m == nullptr) return;
  FLAC__StreamMetadata_VorbisComment_Entry* entry =
      fromjs<FLAC__StreamMetadata_VorbisComment_Entry>(info[1]);
  if (entry == nullptr) return;
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__StreamMetadata*,
                        FLAC__StreamMetadata_VorbisComment_Entry*>(
          cb,
          [](BindingWorker<void, FLAC__StreamMetadata*,
                           FLAC__StreamMetadata_VorbisComment_Entry*>* worker,
             FLAC__StreamMetadata* m,
             FLAC__StreamMetadata_VorbisComment_Entry* entry) {
            if (!FLAC__metadata_object_vorbiscomment_append_comment(m, *entry,
                                                                    true)) {
              worker->SetErrorMessage("Failed to append comment");
            }
          },
          m, entry));
}

NAN_MODULE_INIT(init_metadata_object) {
  Local<Object> obj = Nan::New<Object>();

  SET_METHOD(new, __FLAC__metadata_object_new)
  SET_METHOD(delete, __FLAC__metadata_object_delete)
  SET_METHOD(picture_set_mime_type,
             __FLAC__metadata_object_picture_set_mime_type)
  SET_METHOD(picture_set_description,
             __FLAC__metadata_object_picture_set_description)
  SET_METHOD(picture_set_data, __FLAC__metadata_object_picture_set_data)
  SET_METHOD(picture_is_legal, __FLAC__metadata_object_picture_is_legal)
  SET_METHOD(vorbiscomment_remove_entries_matching,
             __FLAC__metadata_object_vorbiscomment_remove_entries_matching)
  SET_METHOD(vorbiscomment_entry_from_name_value_pair,
             __FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair)
  SET_METHOD(vorbiscomment_append_comment,
             __FLAC__metadata_object_vorbiscomment_append_comment)

  Nan::Set(target, Nan::New("metadata_object").ToLocalChecked(), obj);
}
