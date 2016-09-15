#include <node.h>
#include "Userwrap.h"
#include "Groupwrap.h"
#include "Sessionwrap.h"
#include "Directorywrap.h"



namespace Init {

using v8::Local;
using v8::Object;
using namespace WaDirectory_View;
void InitAll(Local<Object> exports) {
	WaDirectory_View::Userwrap::Init(exports);
	WaDirectory_View::Groupwrap::Init(exports);
	WaDirectory_View::Sessionwrap::Init(exports);
	WaDirectory_View::Directorywrap::Init(exports);
}

NODE_MODULE(addon, InitAll)

}