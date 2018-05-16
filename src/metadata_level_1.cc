#include <FLAC/metadata.h>
#include <nan.h>
#include "binding.h"

#define CHECK_ITERATOR_STATUS(it)                                   \
  worker->SetErrorMessage(FLAC__Metadata_SimpleIteratorStatusString \
                              [FLAC__metadata_simple_iterator_status(it)]);

using namespace v8;
using namespace node;

template <>
Local<Object> StructToJs(FLAC__Metadata_SimpleIterator* i) {
  return Nan::NewBuffer((char*)i, 0,
                        [](char* i, void* it) {
                          FLAC__metadata_simple_iterator_delete(
                              (FLAC__Metadata_SimpleIterator*)it);
                        },
                        i)
      .ToLocalChecked();
}

NAN_METHOD(__FLAC__metadata_simple_iterator_new) {
  FLAC__Metadata_SimpleIterator* it = FLAC__metadata_simple_iterator_new();
  if (it != nullptr) {
    info.GetReturnValue().Set(StructToJs(it));
  } else {
    info.GetReturnValue().SetNull();
  }
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_new) {
  NEW_CALLBACK(cb)
  Nan::AsyncQueueWorker(new BindingWorker<FLAC__Metadata_SimpleIterator*>(
      cb, [](BindingWorker<FLAC__Metadata_SimpleIterator*>* worker) {
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
      [](BindingWorker<void, FLAC__Metadata_SimpleIterator*>* worker,
         FLAC__Metadata_SimpleIterator* it) {
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
      [](BindingWorker<FLAC__Metadata_SimpleIteratorStatus,
                       FLAC__Metadata_SimpleIterator*>* worker,
         FLAC__Metadata_SimpleIterator* it) {
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
  Nan::Utf8String* filename = new Nan::Utf8String(info[1]);
  FLAC__bool read_only = Nan::To<int>(info[2]).FromMaybe(0);
  FLAC__bool preserve_file_stats = Nan::To<int>(info[3]).FromMaybe(0);
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__Metadata_SimpleIterator*, Nan::Utf8String*,
                        FLAC__bool, FLAC__bool>(
          cb,
          [](BindingWorker<void, FLAC__Metadata_SimpleIterator*,
                           Nan::Utf8String*, FLAC__bool, FLAC__bool>* worker,
             FLAC__Metadata_SimpleIterator* it, Nan::Utf8String* filename,
             FLAC__bool read_only, FLAC__bool preserve_file_stats) {
            if (!FLAC__metadata_simple_iterator_init(it, **filename, read_only,
                                                     preserve_file_stats)) {
              CHECK_ITERATOR_STATUS(it)
            }
            delete filename;
          },
          it, filename, read_only, preserve_file_stats));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_is_writable) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_writable(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_is_writable) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_is_writable(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_next) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_next(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_next) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_next(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_prev) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_prev(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_prev) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_prev(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_is_last) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_last(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_is_last) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__bool, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_is_last(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_get_block_offset) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  off_t r = FLAC__metadata_simple_iterator_get_block_offset(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_get_block_offset) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<off_t, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<off_t, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_get_block_offset(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_get_block_type) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__MetadataType r = FLAC__metadata_simple_iterator_get_block_type(it);
  info.GetReturnValue().Set(StructToJs(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_get_block_type) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__MetadataType, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__MetadataType, FLAC__Metadata_SimpleIterator*>*
                 worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_get_block_type(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_get_block_length) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  unsigned r = FLAC__metadata_simple_iterator_get_block_length(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_get_block_length) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<unsigned, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<unsigned, FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) {
            return FLAC__metadata_simple_iterator_get_block_length(it);
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_get_application_id) {
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

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_get_application_id) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__byte id[4];
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__byte*, FLAC__Metadata_SimpleIterator*,
                        FLAC__byte*>(
          cb,
          [](BindingWorker<FLAC__byte*, FLAC__Metadata_SimpleIterator*,
                           FLAC__byte*>* worker,
             FLAC__Metadata_SimpleIterator* it, FLAC__byte* id) -> FLAC__byte* {
            if (FLAC__metadata_simple_iterator_get_application_id(it, id)) {
              return id;
            }
            CHECK_ITERATOR_STATUS(it)
            return nullptr;
          },
          it, id));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_get_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* r = FLAC__metadata_simple_iterator_get_block(it);
  info.GetReturnValue().Set(StructToJs(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_get_block) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::AsyncQueueWorker(
      new BindingWorker<FLAC__StreamMetadata*, FLAC__Metadata_SimpleIterator*>(
          cb,
          [](BindingWorker<FLAC__StreamMetadata*,
                           FLAC__Metadata_SimpleIterator*>* worker,
             FLAC__Metadata_SimpleIterator* it) -> FLAC__StreamMetadata* {
            FLAC__StreamMetadata* r =
                FLAC__metadata_simple_iterator_get_block(it);
            if (r) {
              return r;
            }
            CHECK_ITERATOR_STATUS(it)
            return nullptr;
          },
          it));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_set_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if (m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_set_block(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_set_block) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* data = fromjs<FLAC__StreamMetadata>(info[1]);
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__Metadata_SimpleIterator*,
                                          FLAC__StreamMetadata*, FLAC__bool>(
      cb,
      [](BindingWorker<void, FLAC__Metadata_SimpleIterator*,
                       FLAC__StreamMetadata*, FLAC__bool>* worker,
         FLAC__Metadata_SimpleIterator* it, FLAC__StreamMetadata* block,
         FLAC__bool use_padding) {
        if (!FLAC__metadata_simple_iterator_set_block(it, block, use_padding)) {
          CHECK_ITERATOR_STATUS(it)
        }
      },
      it, data, use_padding));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_insert_block_after) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if (m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r =
      FLAC__metadata_simple_iterator_insert_block_after(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_insert_block_after) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* data = fromjs<FLAC__StreamMetadata>(info[1]);
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  Nan::AsyncQueueWorker(new BindingWorker<void, FLAC__Metadata_SimpleIterator*,
                                          FLAC__StreamMetadata*, FLAC__bool>(
      cb,
      [](BindingWorker<void, FLAC__Metadata_SimpleIterator*,
                       FLAC__StreamMetadata*, FLAC__bool>* worker,
         FLAC__Metadata_SimpleIterator* it, FLAC__StreamMetadata* block,
         FLAC__bool use_padding) {
        if (!FLAC__metadata_simple_iterator_insert_block_after(it, block,
                                                               use_padding)) {
          CHECK_ITERATOR_STATUS(it)
        }
      },
      it, data, use_padding));
}

NAN_METHOD(__FLAC__metadata_simple_iterator_delete_block) {
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool use_padding = Nan::To<int>(info[1]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_delete_block(it, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_ASYNC_METHOD(__FLAC__metadata_simple_iterator_delete_block) {
  NEW_CALLBACK(cb)
  FLAC__Metadata_SimpleIterator* it =
      UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  Nan::AsyncQueueWorker(
      new BindingWorker<void, FLAC__Metadata_SimpleIterator*, FLAC__bool>(
          cb,
          [](BindingWorker<void, FLAC__Metadata_SimpleIterator*, FLAC__bool>*
                 worker,
             FLAC__Metadata_SimpleIterator* it, FLAC__bool use_padding) {
            if (!FLAC__metadata_simple_iterator_delete_block(it, use_padding)) {
              CHECK_ITERATOR_STATUS(it)
            }
          },
          it, use_padding));
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

  SET_METHOD(new, __FLAC__metadata_simple_iterator_new)
  SET_METHOD(delete, __FLAC__metadata_simple_iterator_delete)
  SET_METHOD(status, __FLAC__metadata_simple_iterator_status)
  SET_METHOD(init, __FLAC__metadata_simple_iterator_init)
  SET_METHOD(is_writable, __FLAC__metadata_simple_iterator_is_writable)
  SET_METHOD(next, __FLAC__metadata_simple_iterator_next)
  SET_METHOD(prev, __FLAC__metadata_simple_iterator_prev)
  SET_METHOD(is_last, __FLAC__metadata_simple_iterator_is_last)
  SET_METHOD(get_block_offset,
             __FLAC__metadata_simple_iterator_get_block_offset)
  SET_METHOD(get_block_type, __FLAC__metadata_simple_iterator_get_block_type)
  SET_METHOD(get_block_length,
             __FLAC__metadata_simple_iterator_get_block_length)
  SET_METHOD(get_application_id,
             __FLAC__metadata_simple_iterator_get_application_id)
  SET_METHOD(get_block, __FLAC__metadata_simple_iterator_get_block)
  SET_METHOD(set_block, __FLAC__metadata_simple_iterator_set_block)
  SET_METHOD(insert_block_after,
             __FLAC__metadata_simple_iterator_insert_block_after)
  SET_METHOD(delete_block, __FLAC__metadata_simple_iterator_delete_block)

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

  Nan::Set(target, Nan::New("metadata_simple_iterator").ToLocalChecked(), obj);
}
