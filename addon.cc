#include <node.h>
#include "Userwrap.h"
#include "Groupwrap.h"
#include "Sessionwrap.h"
#include "Directorywrap.h"
#include "DirectorywrapAsynchro.h"

using namespace WaDirectorywrapAsynchro_data_v8;

namespace WaDirectorywrap_data_v8 {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  Userwrap::Init(exports);
  Groupwrap::Init(exports);
  Sessionwrap::Init(exports);
  Directorywrap::Init(exports);
  DirectorywrapAsynchro::Init(exports);
  GroupwrapAsynchro::Init(exports);
  UserwrapAsynchro::Init(exports);
  SessionwrapAsynchro::Init(exports);  
}

NODE_MODULE(addon, InitAll)

}