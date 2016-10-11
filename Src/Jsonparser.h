#pragma once
#include<string>
#include<vector>
using namespace std;
namespace WaDirectory_Data
{
	
	class Jsonparser
	{
		string Url, UrlXml;
		

	public:
		Jsonparser();
		Jsonparser(string Url, string UrlXml);
		~Jsonparser();
		string cookie;
		string login(string Username, string Password);
		bool Logout();
		bool currentUserBelongsTo(string Idgroup, string Namegroup);
		vector<std::string> currentuser();
		string getWASID();
		string GetUrl();
		string GetUrlXML();
		int GetMaxAgeTtl(const string Input);
		void SetUrl(string Url);
		void SetUrlXML(string Url);
		bool isvalid(string Username, string Password);
		double Ttl = 0;
	};
}
