#pragma once
#include<node.h>
#include"JsonData.h"
#include "curl/curl.h"
#include "curl/easy.h"
namespace WaDirectory_data
{
	class JsonData;
	class curlcpp
	{
	private: 
		string Url;
	public:
		curlcpp(string Url);
		
		~curlcpp();
		
		JsonData data, dataheaderstr;
		
		size_t write_databody(void *ptr, size_t size, size_t nmemb);
		
		static size_t WriteDataCallbackbody(void *ptr, size_t size, size_t nmemb, void* pInstance);
		
		size_t write_dataheader(void *ptr, size_t size, size_t nmemb);
		
		static size_t WriteDataCallbackheader(void *ptr, size_t size, size_t nmemb, void* pInstance);
		
		CURL *curl;
		
		CURLcode res;

		std::string m_data;
		
		void initall(CURL *curl2);

		string login(string username, string password, string url);
		
		void curentuser(string url, string cookie);

		void isvalid(string username, string password, string url);
		
		void currentUserBelongsTo(string url, string Idgroup, string Namegroup, string cookie);
		
		void Logout(string url, string cookie);
		
		string getWASID();
	private:
		void CurlCppSetOption(string Url,CURL* curl);
	};
}
