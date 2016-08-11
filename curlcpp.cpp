#pragma warning(disable:4996)
#include<node.h>
#include "curlcpp.h"

using namespace std;
namespace WaDirectory_data
{

	curlcpp::curlcpp()
	{
		curl = curl_easy_init();
		this->test = "var test";
	}


	curlcpp::~curlcpp()
	{

	}
	size_t curlcpp::write_databody(void *ptr, size_t size, size_t nmemb) {

		size_t numBytes = size * nmemb;


		data.file->write((char*)ptr, numBytes);


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


		dataheaderstr.file->write((char*)ptr, numBytes);


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
		//this->test = "";
		this->dataheaderstr.str = "";
		struct curl_slist *headers = NULL;

		headers = curl_slist_append(headers, header_accept.c_str());

		curl = curl_easy_init();

	}


	string curlcpp::login(string username, string password, string url)
	{

		curl = curl_easy_init();

		fstream file("contentclass.json", ios_base::out | ios_base::ate);
		fstream fileheader("headerclass.txt", ios_base::out | ios_base::ate);
		string dataheader;
		dataheaderstr.file = &fileheader;
		data.file = &file;
		//
		if (curl) {

			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13");

			/* set timeout */
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			std::string data = "[\"" + username + "\",\"" + password + "\"]";
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  // for --insecure option
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			//curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "COOKIE2.txt");
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");



			//curl_easy_setopt(curl, CURLOPT_COOKIE, "tool=curl; fun=yes;");


			res = curl_easy_perform(curl);
			res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
			int i;
			data2_cookie.assign(cookies->data);


			curl_easy_cleanup(curl);
			return data2_cookie;

		}



	}


	void curlcpp::curentuser(string url, string cookie)
	{

		curl = curl_easy_init();

		fstream file("contentclasscurentuser.json", ios_base::out | ios_base::ate);
		fstream fileheader("headerclasscurentuser.txt", ios_base::out | ios_base::ate);
		dataheaderstr.file = &fileheader;
		data.file = &file;
		//
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13");
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			//	curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());

			//curl_easy_setopt(curl, CURLOPT_COOKIE, "tool=curl; fun=yes;");
			res = curl_easy_perform(curl);
			//res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
			int i;

			//	data2_cookie = cookies->data;

			curl_easy_cleanup(curl);

		}




	}


	void curlcpp::currentUserBelongsTo(string url, string Idgroup, string Namegroup, string cookie)
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
		fstream file("contentclasscurrentUserBelongsTo.json", ios_base::out | ios_base::ate);
		fstream fileheader("headerclasscurrentUserBelongsTo.txt", ios_base::out | ios_base::ate);

		dataheaderstr.file = &fileheader;
		data.file = &file;
		//
		if (curl) {

			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13");
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataparametre.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, dataparametre.length());
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			//curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");


			//curl_easy_setopt(curl, CURLOPT_COOKIE, "tool=curl; fun=yes;");
			res = curl_easy_perform(curl);

			int i;

			//data2_cookie = cookies->data;

			curl_easy_cleanup(curl);

		}

	}


	void curlcpp::Logout(string url, string cookie)
	{


		curl = curl_easy_init();

		fstream file("contentclasslogout.json", ios_base::out | ios_base::ate);
		fstream fileheader("headerclasslogout.txt", ios_base::out | ios_base::ate);
		dataheaderstr.file = &fileheader;
		data.file = &file;
		//
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13");
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallbackbody);
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteDataCallbackheader);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
			//curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "COOKIE2.txt");
			curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie.c_str());
			//curl_easy_setopt(curl, CURLOPT_COOKIE, "tool=curl; fun=yes;");
			res = curl_easy_perform(curl);
			//res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

			curl_easy_cleanup(curl);

		}



	}
	string curlcpp::getWASID()
	{
		std::string sub = "";
		std::string strwasid("WASID	");
		string line;
		ifstream myfile("COOKIE2.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				std::size_t found = line.find(strwasid);
				if (found != std::string::npos)
				{
					int pos = line.find("WASID	");
					sub = line.substr(pos + 6);
				}
			}
			myfile.close();
		}

		else cout << "Unable to open file";
		return sub;

	}
}