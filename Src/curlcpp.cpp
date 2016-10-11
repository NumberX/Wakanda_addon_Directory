#pragma warning(disable:4996)
#include<node.h>
#include "curlcpp.h"

using namespace std;
namespace WaDirectory_Data
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

	void curlcpp::initall(CURL *curl2)
	{
		string header_accept = "Accept: application/json ";
		
		this->data.str = "";
		
		this->dataheaderstr.str = "";
		
		struct curl_slist *headers = NULL;

		headers = curl_slist_append(headers, header_accept.c_str());

		curl = curl_easy_init();

	}

	void curlcpp::isvalid(string username, string password, string url)
	{



		CURL *curl2;

		curl2 = curl_easy_init();

		initall(curl2);

		if (curl2) {


			this->CurlCppSetOption(url, curl2);

			std::string data = "[\"" + username + "\",\"" + password + "\"]";

			curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0);  // for --insecure option

			curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, data.c_str());

			curl_easy_setopt(curl2, CURLOPT_POSTFIELDSIZE, data.length());

			curl_easy_setopt(curl2, CURLOPT_POST, 1);

			curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);

			curl_easy_setopt(curl2, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);

			curl_easy_setopt(curl2, CURLOPT_WRITEDATA, this);

			curl_easy_setopt(curl2, CURLOPT_HEADERDATA, this);

			res = curl_easy_perform(curl2);


			curl_easy_cleanup(curl2);


		}

	}
	string curlcpp::login(string username, string password, string url)
	{
		string Resultat = "";

		CURL *curl2;

		curl2 = curl_easy_init();

		initall(curl2);
		
		string UrlLogin = this->Url + url;
		
		if (curl2) {

			this->CurlCppSetOption(UrlLogin,curl2);

			std::string data = "[\"" + username + "\",\"" + password + "\"]";
			
			curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0);  // for --insecure option
			
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, data.c_str());
			
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDSIZE, data.length());
			
			curl_easy_setopt(curl2, CURLOPT_POST, 1);
			
			curl_easy_setopt(curl2, CURLOPT_COOKIEFILE, "");

            res = curl_easy_perform(curl2);
		
			curl_slist *cookies1; 
			
			cookies1->data = "";

			res = curl_easy_getinfo(curl2, CURLINFO_COOKIELIST, &cookies1);
			
            curl_easy_cleanup(curl2);
			
			Resultat=cookies1->data;

			

			

		}


		return Resultat;

	}
	void curlcpp::CurlCppSetOption(string Url,CURL* curl)
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
		CURL *curl2;
		
		curl2 = curl_easy_init();

		initall(curl2);

		string UrlCurentUser = this->Url + UrlCurrentUserin;
		if (curl2) {
			
			CurlCppSetOption(UrlCurentUser,curl2);

			curl_easy_setopt(curl2, CURLOPT_COOKIELIST, cookie.c_str());
			
			curl_easy_setopt(curl2, CURLOPT_HTTPGET, 1);

			res = curl_easy_perform(curl2);
		
			curl_easy_cleanup(curl2);

		}


	}


	void curlcpp::currentUserBelongsTo(string UrlcurrentUserBelongsToIn, string Idgroup, string Namegroup, string cookie)
	{
		CURL *curl2;

		curl2 = curl_easy_init();

		initall(curl2);

		std::string dataparametre;
		
		if (Idgroup.length() > 0)
		{
			dataparametre = "[\"" + Idgroup + "\"]";
			
		}

		
		string UrlcurrentUserBelongsTo = this->Url + UrlcurrentUserBelongsToIn;

		if (curl2) {

			this->CurlCppSetOption(UrlcurrentUserBelongsTo,curl2);
			
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, dataparametre.c_str());
			
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDSIZE, dataparametre.length());
			
			curl_easy_setopt(curl2, CURLOPT_POST, 1);
			
			curl_easy_setopt(curl2, CURLOPT_COOKIELIST, cookie.c_str());
			
            res = curl_easy_perform(curl2);

			curl_easy_cleanup(curl2);
			

			

		}

	}


	void curlcpp::Logout(string UrlLogoutIn, string cookie)
	{

		CURL *curl2;

		curl2 = curl_easy_init();

		initall(curl2);

		string UrlLogout = this->Url + UrlLogoutIn;
		
		if (curl2) {
			
			this->CurlCppSetOption(UrlLogout, curl2);

			curl_easy_setopt(curl2, CURLOPT_HTTPGET, 1);

			curl_easy_setopt(curl2, CURLOPT_COOKIELIST, cookie.c_str());
			
			res = curl_easy_perform(curl2);
			
			curl_easy_cleanup(curl2);

		}



	}

}