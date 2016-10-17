#pragma once
#include<string>
using namespace std;
namespace WaDirectory_Data
{ 
class UnionUserSession
{
	
public:
	UnionUserSession();
	~UnionUserSession();
	string IdUser;
	string cookies;
	string Username;
	double MaxAgeTtl;
	string getWASID();
};

}