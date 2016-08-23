#include "Jsonparser.h"
#include"curlcpp.h"
#include "rapidjson\document.h"
#include<string>
#include<vector>
using namespace std;
using namespace rapidjson;

namespace WaDirectory_data
{
	Jsonparser::Jsonparser()
	{

		this->Url = "";
		this->UrlXml = "";

	}


	Jsonparser::~Jsonparser()
	{
	}

	Jsonparser::Jsonparser(string Url, string UrlXml)
	{
		this->Url = Url;
		this->UrlXml = UrlXml;

	}
	string Jsonparser::GetUrl(){
		return this->Url;
	}
	string Jsonparser::GetUrlXML(){
		return this->UrlXml;
	}
	void Jsonparser::SetUrl(string Url){
	   this->Url=Url;
	}
	void Jsonparser::SetUrlXML(string UrlXml){
	
		this->UrlXml = UrlXml;
	}

	string Jsonparser::login(string Username, string Password)
	{

		curlcpp curltest("");

		curltest.initall();
		//"http://localhost:8081/rest/$directory/login"
		
		string Url = this->Url + "/rest/$directory/login";
		
		this->cookie = curltest.login(Username, Password, Url);

		if (curltest.res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;
		else {

			Document document;

			document.Parse(curltest.data.str.c_str());
			
			if (document["result"].GetBool() == true)
			{
				 return (getWASID());
			}

			if (document["result"].GetBool() == false)return "";
		}
		return "";
	}

	string Jsonparser::getWASID()
	{
		string sub = "";

		int pos = static_cast<int>(cookie.find("WASID	"));

		sub = cookie.substr(pos + 6);
		
		return sub;
	
	}

	bool Jsonparser::Logout()
	{

		curlcpp curltest("");

		curltest.initall();

		string Url = this->GetUrl() + "/rest/$directory/logout";

		curltest.Logout(Url, this->cookie);

		this->cookie = "";

		if (curltest.res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;

		else {

			Document document;

			document.Parse(curltest.data.str.c_str());

			if (document["result"].GetBool() == true)return true;

			if (document["result"].GetBool() == false)return false;
		}
		return false;
	}


	bool Jsonparser::currentUserBelongsTo(string Idgroup, string Namegroup)
	{

		curlcpp curltest("");

		curltest.initall();

		string Url = this->GetUrl() + "/rest/$directory/currentUserBelongsTo";

		curltest.currentUserBelongsTo(Url, Idgroup, Namegroup, this->cookie);

		if (curltest.res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;

		else {

			Document document;

			document.Parse(curltest.data.str.c_str());

			if (document["result"].GetBool() == true)return true;

			if (document["result"].GetBool() == false)return false;

		}
		return false;
	}


	vector<std::string> Jsonparser::currentuser()
	{

		std::vector<std::string> resultat;

		curlcpp curltest("");

		curltest.initall();

		string Url = this->GetUrl() + "/rest/$directory/currentUser";

		curltest.curentuser(Url, this->cookie);

		if (curltest.res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;

		else {

			Document document;

			document.Parse(curltest.data.str.c_str());

			if (document["result"].IsNull())
			{

			}
			else
			{

				for (Value::ConstMemberIterator Iterator = document["result"].MemberBegin();
					Iterator != document["result"].MemberEnd(); ++Iterator)
				{
					if (Iterator->name == "userName") {
						resultat.push_back(Iterator->value.GetString());
					}
					if (Iterator->name == "fullName") {
						resultat.push_back(Iterator->value.GetString());
					}
					if (Iterator->name == "ID") {
						resultat.push_back(Iterator->value.GetString());
					}

				}

			}

		}
		return resultat;

		
	}
}