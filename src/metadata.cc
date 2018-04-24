#include <nan.h>
#include <FLAC/metadata.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_new) {
  FLAC__Metadata_SimpleIterator* it = FLAC__metadata_simple_iterator_new();
  if (it != nullptr) {
    info.GetReturnValue().Set(WrapPtr(it).ToLocalChecked());
  } else {
    info.GetReturnValue().SetNull();
  }
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_delete) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__metadata_simple_iterator_delete(it);
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_status) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__Metadata_SimpleIteratorStatus r = FLAC__metadata_simple_iterator_status(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_init) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  Nan::Utf8String filename(info[1]);
  FLAC__bool read_only = Nan::To<int>(info[2]).FromMaybe(0);
  FLAC__bool preserve_file_stats = Nan::To<int>(info[3]).FromMaybe(0);
  FLAC__bool r = FLAC__metadata_simple_iterator_init(it, *filename, read_only, preserve_file_stats);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_is_writable) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_writable(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_next) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_next(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_prev) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_prev(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_is_last) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool r = FLAC__metadata_simple_iterator_is_last(it);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_offset) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  off_t r = FLAC__metadata_simple_iterator_get_block_offset(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}


NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_type) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__MetadataType r = FLAC__metadata_simple_iterator_get_block_type(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_block_length) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  unsigned r = FLAC__metadata_simple_iterator_get_block_length(it);
  info.GetReturnValue().Set(Nan::New<Number>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_get_application_id) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__byte id[4];
  FLAC__bool r = FLAC__metadata_simple_iterator_get_application_id(it, id);
  if(r) {
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
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* r = FLAC__metadata_simple_iterator_get_block(it);
  info.GetReturnValue().Set(StructToJs(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_set_block) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if(m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_set_block(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_insert_block_after) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__StreamMetadata* m = fromjs<FLAC__StreamMetadata>(info[1]);
  if(m == nullptr) return;
  FLAC__bool use_padding = Nan::To<int>(info[2]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_insert_block_after(it, m, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_METHOD(NODE_FLAC__metadata_simple_iterator_delete_block) {
  FLAC__Metadata_SimpleIterator* it = UnwrapPtr<FLAC__Metadata_SimpleIterator>(info[0]);
  FLAC__bool use_padding = Nan::To<int>(info[1]).FromMaybe(1);
  FLAC__bool r = FLAC__metadata_simple_iterator_delete_block(it, use_padding);
  info.GetReturnValue().Set(Nan::New<Boolean>(r));
}

NAN_PROPERTY_GETTER(SimpleIteratorStatus) {
  Nan::Utf8String p(property);
  std::string PropertyName(*p);

  if(PropertyName == "OK") info.GetReturnValue().Set(0);
  else if(PropertyName == "ILLEGAL_INPUT") info.GetReturnValue().Set(1);
  else if(PropertyName == "ERROR_OPENING_FILE") info.GetReturnValue().Set(2);
  else if(PropertyName == "NOT_A_FLAC_FILE") info.GetReturnValue().Set(3);
  else if(PropertyName == "NOT_WRITABLE") info.GetReturnValue().Set(4);
  else if(PropertyName == "BAD_METADATA") info.GetReturnValue().Set(5);
  else if(PropertyName == "READ_ERROR") info.GetReturnValue().Set(6);
  else if(PropertyName == "SEEK_ERROR") info.GetReturnValue().Set(7);
  else if(PropertyName == "WRITE_ERROR") info.GetReturnValue().Set(8);
  else if(PropertyName == "RENAME_ERROR") info.GetReturnValue().Set(9);
  else if(PropertyName == "UNLINK_ERROR") info.GetReturnValue().Set(10);
  else if(PropertyName == "MEMORY_ALLOCATION_ERROR") info.GetReturnValue().Set(11);
  else if(PropertyName == "INTERNAL_ERROR") info.GetReturnValue().Set(12);
  else info.GetReturnValue().SetUndefined();
}

NAN_INDEX_GETTER(SimpleIteratorStatusString) {
  if(index < 13) {
    info.GetReturnValue().Set(Nan::New(FLAC__Metadata_SimpleIteratorStatusString[index]).ToLocalChecked());
  } else {
    info.GetReturnValue().SetUndefined();
  }
}

NAN_INDEX_ENUMERATOR(SimpleIteratorStatusString) {
  Local<Array> array = Nan::New<Array>();
  for(int i = 0; i < 13; i++) Nan::Set(array, i, Nan::New(i));
  info.GetReturnValue().Set(array);
}

NAN_MODULE_INIT(init_metadata) {
  Local<Object> obj = Nan::New<Object>();

  Nan::SetMethod(obj, "new", NODE_FLAC__metadata_simple_iterator_new);
  Nan::SetMethod(obj, "delete", NODE_FLAC__metadata_simple_iterator_delete);
  Nan::SetMethod(obj, "status", NODE_FLAC__metadata_simple_iterator_status);
  Nan::SetMethod(obj, "init", NODE_FLAC__metadata_simple_iterator_init);
  Nan::SetMethod(obj, "is_writable", NODE_FLAC__metadata_simple_iterator_is_writable);
  Nan::SetMethod(obj, "next", NODE_FLAC__metadata_simple_iterator_next);
  Nan::SetMethod(obj, "prev", NODE_FLAC__metadata_simple_iterator_prev);
  Nan::SetMethod(obj, "is_last", NODE_FLAC__metadata_simple_iterator_is_last);
  Nan::SetMethod(obj, "get_block_offset", NODE_FLAC__metadata_simple_iterator_get_block_offset);
  Nan::SetMethod(obj, "get_block_type", NODE_FLAC__metadata_simple_iterator_get_block_type);
  Nan::SetMethod(obj, "get_block_length", NODE_FLAC__metadata_simple_iterator_get_block_length);
  Nan::SetMethod(obj, "get_application_id", NODE_FLAC__metadata_simple_iterator_get_application_id);
  Nan::SetMethod(obj, "get_block", NODE_FLAC__metadata_simple_iterator_get_block);
  Nan::SetMethod(obj, "set_block", NODE_FLAC__metadata_simple_iterator_set_block);
  Nan::SetMethod(obj, "insert_block_after", NODE_FLAC__metadata_simple_iterator_insert_block_after);
  Nan::SetMethod(obj, "delete_block", NODE_FLAC__metadata_simple_iterator_delete_block);

  Local<ObjectTemplate> SimpleIteratorStatusTemplate = Nan::New<ObjectTemplate>();
  Nan::SetNamedPropertyHandler(SimpleIteratorStatusTemplate, SimpleIteratorStatus);
  Nan::Set(obj, Nan::New("SimpleIteratorStatus").ToLocalChecked(), Nan::NewInstance(SimpleIteratorStatusTemplate).ToLocalChecked());

  Local<ObjectTemplate> SimpleIteratorStatusStringTemplate = Nan::New<ObjectTemplate>();
  Nan::SetIndexedPropertyHandler(SimpleIteratorStatusStringTemplate, SimpleIteratorStatusString, nullptr, nullptr, nullptr, SimpleIteratorStatusString);
  Nan::Set(obj, Nan::New("SimpleIteratorStatusString").ToLocalChecked(), Nan::NewInstance(SimpleIteratorStatusStringTemplate).ToLocalChecked());

  Nan::Set(target, Nan::New("metadata").ToLocalChecked(), obj);
}