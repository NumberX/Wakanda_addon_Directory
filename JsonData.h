#pragma once
#include<iostream>
#include <fstream>
#include<string>
using namespace std;
namespace WaDirectory_data
{ 
class JsonData
{
public:
	JsonData();
	~JsonData();
	fstream *file;
	string str;
};
}
