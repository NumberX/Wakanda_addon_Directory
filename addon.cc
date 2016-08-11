#include <node.h>
#include "Userwrap.h"
#include "Groupwrap.h"
#include "Sessionwrap.h"
#include "Directorywrap.h"
namespace WaDirectorywrap_data_v8 {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  Userwrap::Init(exports);
  Groupwrap::Init(exports);
  Sessionwrap::Init(exports);
  Directorywrap::Init(exports);
}

NODE_MODULE(addon, InitAll)

}