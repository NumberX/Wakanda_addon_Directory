#include "Jsonparser.h"
#include"curlcpp.h"
#include "rapidjson\document.h"
#include<string>
#include<vector>
using namespace std;
using namespace rapidjson;

namespace WaDirectory_Data
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
		if (isvalid(Username, Password)==true)
		{ 
		curlcpp *curltest;

		curltest = new curlcpp("");




		string Url = this->Url + "/rest/$directory/login";

		this->cookie = "";
		
		this->cookie = curltest->login(Username, Password, Url);


		if (curltest->res != CURLE_OK)

		{
			cerr << "ERROR: " << curl_easy_strerror(curltest->res) << endl;

		}
		else {

			Document document;

			document.Parse(curltest->data.str.c_str());

			
			
			if (document["result"].GetBool() == true)
			{
				return (this->cookie);
			}

			if (document["result"].GetBool() == false)
			{
				return "";

			}
		}
		
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

		curlcpp *curltest;

		curltest = new curlcpp("");

		string Url = this->GetUrl() + "/rest/$directory/logout";

		curltest->Logout(Url, this->cookie);

		this->cookie = "";

		if (curltest->res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest->res) << endl;

		else {

			Document document;

			document.Parse(curltest->data.str.c_str());

			if (document["result"].GetBool() == true)return true;

			if (document["result"].GetBool() == false)return false;
		}
		return false;
	}

	bool Jsonparser::isvalid(string Username, string Password)
	{
		curlcpp *curltest;

		curltest = new curlcpp("");

		string Url = this->GetUrl() + "/rest/$directory/login";

		curltest->isvalid(Username,Password,Url);

		this->cookie = "";

		if (curltest->res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest->res) << endl;

		else {

			Document document;

			document.Parse(curltest->data.str.c_str());

			if (document["result"].GetBool() == true)return true;

			if (document["result"].GetBool() == false)return false;
		}
		return false;


	}
	bool Jsonparser::currentUserBelongsTo(string Idgroup, string Namegroup)
	{

		curlcpp *curltest;

		curltest = new curlcpp("");


		string Url = this->GetUrl() + "/rest/$directory/currentUserBelongsTo";

		
		if (Idgroup.length()>1)
		{
			curltest->currentUserBelongsTo(Url, Idgroup, "", this->cookie);
		}
		if (Namegroup.length()>1)
		{
			curltest->currentUserBelongsTo(Url, Namegroup, "", this->cookie);
		}

		if (curltest->res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest->res) << endl;

		else {

			Document document;

			document.Parse(curltest->data.str.c_str());

			if (document["result"].GetBool() == true)
			{
			
				return true;
			}
			if (document["result"].GetBool() == false){ return false; }

		}
		return false;
	}


	vector<std::string> Jsonparser::currentuser()
	{

		std::vector<std::string> resultat;

		curlcpp *curltest;

		curltest = new curlcpp("");

		string Url = this->GetUrl() + "/rest/$directory/currentUser";

		curltest->curentuser(Url, this->cookie);

		if (curltest->res != CURLE_OK)

			cerr << "ERROR: " << curl_easy_strerror(curltest->res) << endl;

		else {

			Document document;

			document.Parse(curltest->data.str.c_str());

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