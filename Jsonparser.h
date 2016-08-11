#pragma once
#include<string>
#include<vector>
using namespace std;
namespace WaDirectory_data
{
	class curlcpp;
	class Jsonparser
	{
	public:
		Jsonparser();
		~Jsonparser();
		string cookie;
		string login(string Username, string Password);
		bool Logout();
		bool currentUserBelongsTo(string Idgroup, string Namegroup);
		vector<std::string> currentuser();
		string getWASID();
	};
}
