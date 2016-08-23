#pragma warning(disable:4996)
#include<node.h>
#include "curlcpp.h"

using namespace std;
namespace WaDirectory_data
{

	curlcpp::curlcpp(string Url)
	{
		this->Url = Url;
		curl = curl_easy_init();
		
	}


	curlcpp::~curlcpp()
	{

	}
	size_t curlcpp::write_databody(void *ptr, size_t size, size_t nmemb) {

		size_t numBytes = size * nmemb;

		(data.str) += string((char*)ptr, numBytes);

		return numBytes;
	}
	size_t curlcpp::WriteDataCallbackbody(void *ptr, size_t size,
		size_t nmemb, void* pInstance)
	{
		return (static_cast<curlcpp*>(pInstance))->write_databody(ptr, size, nmemb);
	}


	size_t curlcpp::write_dataheader(void *ptr, size_t size, size_t nmemb) {

		size_t numBytes = size * nmemb;

		(dataheaderstr.str) += string((char*)ptr, numBytes);

		return numBytes;
	}
	size_t curlcpp::WriteDataCallbackheader(void *ptr, size_t size,
		size_t nmemb, void* pInstance)
	{
		return (static_cast<curlcpp*>(pInstance))->write_dataheader(ptr, size, nmemb);
	}

	void curlcpp::initall()
	{
		string header_accept = "Accept: application/json ";
		
		this->data.str = "";
		
		this->dataheaderstr.str = "";
		
		struct curl_slist *headers = NULL;

		headers = curl_slist_append(headers, header_accept.c_str());

		curl = curl_easy_init();

	}


	string curlcpp::login(string username, string password, string url)
	{
		string Resultat = "";

	//CURL*
		curl = curl_easy_init();

		string dataheader;
		
		string UrlLogin = this->Url + url;
		
		if (curl) {

			this->CurlCppSetOption(UrlLogin);

			std::string data = "[\"" + username + "\",\"" + password + "\"]";
			
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  // for --insecure option
			
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
			
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

            res = curl_easy_perform(curl);
			
			res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
			
            curl_easy_cleanup(curl);
			
			Resultat=cookies->data;

		}
		
		return Resultat;

	}
	void WaDirectory_data::curlcpp::CurlCppSetOption(string Url)
	{


		curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13");

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);

		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

		curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);


	}

	void curlcpp::curentuser(string UrlCurrentUserin, string cookie)
	{

		curl = curl_easy_init();

		string UrlCurentUser = this->Url + UrlCurrentUserin;
		if (curl) {
			
			CurlCppSetOption(UrlCurentUser);

			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);

			res = curl_easy_perform(curl);
		
			curl_easy_cleanup(curl);

		}


	}


	void curlcpp::currentUserBelongsTo(string UrlcurrentUserBelongsToIn, string Idgroup, string Namegroup, string cookie)
	{

		curl = curl_easy_init();

		std::string dataparametre;
		
		if (Idgroup.length() != 0)
		{
			dataparametre = "[\"" + Idgroup + "\"]";
		}
		if (Namegroup.length() != 0)
		{
			dataparametre = "[\"" + Namegroup + "\"]";
		}
		
		string UrlcurrentUserBelongsTo = this->Url + UrlcurrentUserBelongsToIn;

		if (curl) {

			this->CurlCppSetOption(UrlcurrentUserBelongsTo);
			
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataparametre.c_str());
			
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, dataparametre.length());
			
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			
			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			
            res = curl_easy_perform(curl);

			curl_easy_cleanup(curl);

		}

	}


	void curlcpp::Logout(string UrlLogoutIn, string cookie)
	{


		curl = curl_easy_init();

		string UrlLogout = this->Url + UrlLogoutIn;
		
		if (curl) {
			
			this->CurlCppSetOption(UrlLogout);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);

			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			
			res = curl_easy_perform(curl);
			
			curl_easy_cleanup(curl);

		}



	}

}