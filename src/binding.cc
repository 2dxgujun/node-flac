#include "binding.h"
#include <nan.h>

using namespace v8;
using namespace node;

NAN_MODULE_INIT(init_format);
NAN_MODULE_INIT(init_metadata);
NAN_MODULE_INIT(init_metadata_level_1);
NAN_MODULE_INIT(init_metadata_object);

NAN_MODULE_INIT(init) {
  init_format(target);
  init_metadata(target);
  init_metadata_level_1(target);
  init_metadata_object(target);
}

NODE_MODULE(flac_bindings, init);
