#include "Utility.h"
#include<vector>
using namespace std;
using namespace v8;
namespace WaDirectorywrap_data_v8 {

	Utility::Utility()
	{
	}


	Utility::~Utility()
	{
	}
}

Local<Array> WaDirectorywrap_data_v8::Utility::StdVectorToV8Array(Isolate*  isolate, std::vector<std::string>& Vector)
{
	Local<Array> Resultat = Array::New(isolate);
	int i = 0;
	for (auto const& Iterator : Vector) {
		Local<String> result = String::NewFromUtf8(isolate, Iterator.c_str());

		Resultat->Set(i, result);
		i++;
	}

	return Resultat;
}
string WaDirectorywrap_data_v8::Utility::V8Utf8ValueToStdString(v8::Local<v8::Value>& arg)
{
	String::Utf8Value Localv8string(arg);
	
	string Localstdstring(*Localv8string);
	return Localstdstring;
}
