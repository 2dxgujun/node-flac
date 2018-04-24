#include <nan.h>
#include "binding.h"

using namespace v8;
using namespace node;

NAN_MODULE_INIT(init_format);
NAN_MODULE_INIT(init_metadata);

NAN_MODULE_INIT(init) {
  init_format(target);
  init_metadata(target);
}

NODE_MODULE(flac_bindings, init);
