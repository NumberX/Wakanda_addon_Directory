#pragma once
#include <node.h>
#include<vector>
using namespace std;
using namespace v8;
namespace WaDirectorywrap_data_v8 {
	class Utility
	{
	public:
		Utility();
		~Utility();
		Local<Array> StdVectorToV8Array(Isolate*  isolate, std::vector<std::string>& vector);
		string V8Utf8ValueToStdString(v8::Local<v8::Value>& arg);
	};

}