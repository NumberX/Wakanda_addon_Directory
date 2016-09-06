#pragma once
#include<string>
using namespace std;
namespace WaDirectory
{ 
class UnionUserSession
{
	
public:
	UnionUserSession();
	~UnionUserSession();
	string IdUser;
	string cookies;
	string Username;

	string getWASID();
};

}