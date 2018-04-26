#include <FLAC/metadata.h>
#include <nan.h>
#include "binding.h"

#define NAN_ASYNC_METHOD(name) NAN_METHOD(name##_async)
#define NEW_CALLBACK(name)                 \
  Nan::Callback* name = new Nan::Callback( \
      Nan::To<Function>(info[info.Length() - 1]).ToLocalChecked());

using namespace v8;
using namespace node;

template <>
Local<Object> StructToJs(const FLAC__Metadata_SimpleIterator* i) {
  return WrapPtr(i).ToLocalChecked();
}

NAN_METHOD(__FLAC__metadata_simple_iterator_new) {
  FLAC__Metadata_SimpleIterator* it = FLAC__metadata_simple_iterator_new();
  if (it != nullptr) {
    info.GetReturnValue().Set(WrapPtr(it).ToLocalChecked());
  } else {
    info.GetReturnValue().SetNull();
  }
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_new) {
  NEW_CALLBACK(cb)
  Nan::AsyncQueueWorker(new BindingWorker<FLAC__Metadata_SimpleIterator*>(
      cb, [](Nan::AsyncWorker* worker) {
        return FLAC__metadata_simple_iterator_new();
      }));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_delete) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__metadata_simple_iterator_delete(it);
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_delete) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__Metadata_SimpleIterator*>(
      cb,
      [](Nan::AsyncWorker* worker, FLAC__Metadata_SimpleIterator* it) {
        FLAC__metadata_simple_iterator_delete(it);
      },
      it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_status) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__Metadata_SimpleIteratorStatus r =
      FLAC__metadata_simple_iterator_status(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_status) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(new BindingWorker<FLAC__Metadata_SimpleIteratorStatus,
                                          FLAC__Metadata_SimpleIterator*>(
      cb,
      [](Nan::AsyncWorker* worker, FLAC__Metadata_SimpleIterator* it) {
        return FLAC__metadata_simple_iterator_status(it);
      },
      it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_init) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::Utf8String filename(info[1]);
  FLAC__bool read_only = Nan::To<int>(info[2]).FromMaybe(0);
  FLAC__bool preserve_file_stats = Nan::To<int>(info[3]).FromMaybe(0);
  FLAC__bool r = FLAC__metadata_simple_iterator_init(it, *filename, read_only,
                                                     preserve_file_stats);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_init) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::Utf8String filename(info[1]);
  FLAC__bool read_only = Nan::To<int>(info[2]).FromMaybe(0);
  FLAC__bool preserve_file_stats = Nan::To<int>(info[3]).FromMaybe(0);

  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*, char*,
                        FLAC__bool, FLAC__bool>(
          cb,
          [](Nan::AsyncWorker* worker, FLAC__Metadata_SimpleIterator* it,
             char* filename, FLAC__bool read_only,
             FLAC__bool preserve_file_stats) {
            return FLAC__metadata_simple_iterator_init(it, filename, read_only,
                                                       preserve_file_stats);
          },
          it, *filename, read_only, preserve_file_stats));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_is_writable) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_writable(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_next) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_next(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_prev) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_prev(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_is_last) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_last(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_offset) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  off_t r = FLAC__metadata_simple_iterator_get_block_offset(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_type) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__MetadataType r = FLAC__metadata_simple_iterator_get_block_type(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_length) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  unsigned r = FLAC__metadata_simple_iterator_get_block_length(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_application_id) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__byte id[4];
  FLAC__bool r = FLAC__metadata_simple_iterator_get_application_id(it, id);
  if (r) {
    Local<Array> arr = Nan::New<Array>();
    Nan::Set(arr, 0, Nan::New<Number>(id[0]));
    Nan::Set(arr, 1, Nan::New<Number>(id[1]));
    Nan::Set(arr, 2, Nan::New<Number>(id[2]));
    Nan::Set(arr, 3, Nan::New<Number>(id[3]));
    info.GetReturnValue().Set(arr);
  } else {
    info.GetReturnValue().Set(Nan::New<Boolean>(false));
  }
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* r = FLAC__metadata_simple_iterator_get_block(it);
  info.GetReturnValue().Set(StructToJs(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_set_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if (m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_set_block(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_insert_block_after) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if (m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r =
      FLAC__metadata_simple_iterator_insert_block_after(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_delete_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool use_padding = Nan::To<int>(info[1]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_delete_block(it, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

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

#define SET_METHOD(name, func)             \
  Nan::SetMethod(obj, #name "Sync", func); \
  Nan::SetMethod(obj, #name, func##_async);

  SET_METHOD(new, __FLAC__metadata_simple_iterator_new)
  SET_METHOD(delete, __FLAC__metadata_simple_iterator_delete)
  SET_METHOD(status, __FLAC__metadata_simple_iterator_status)
  SET_METHOD(init, __FLAC__metadata_simple_iterator_init)

  Nan::SetMethod(obj, "is_writable",
                 NODE_FLAC__metadata_simple_iterator_is_writable);
  Nan::SetMethod(obj, "next", NODE_FLAC__metadata_simple_iterator_next);
  Nan::SetMethod(obj, "prev", NODE_FLAC__metadata_simple_iterator_prev);
  Nan::SetMethod(obj, "is_last", NODE_FLAC__metadata_simple_iterator_is_last);
  Nan::SetMethod(obj, "get_block_offset",
                 NODE_FLAC__metadata_simple_iterator_get_block_offset);
  Nan::SetMethod(obj, "get_block_type",
                 NODE_FLAC__metadata_simple_iterator_get_block_type);
  Nan::SetMethod(obj, "get_block_length",
                 NODE_FLAC__metadata_simple_iterator_get_block_length);
  Nan::SetMethod(obj, "get_application_id",
                 NODE_FLAC__metadata_simple_iterator_get_application_id);
  Nan::SetMethod(obj, "get_block",
                 NODE_FLAC__metadata_simple_iterator_get_block);
  Nan::SetMethod(obj, "set_block",
                 NODE_FLAC__metadata_simple_iterator_set_block);
  Nan::SetMethod(obj, "insert_block_after",
                 NODE_FLAC__metadata_simple_iterator_insert_block_after);
  Nan::SetMethod(obj, "delete_block",
                 NODE_FLAC__metadata_simple_iterator_delete_block);

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
