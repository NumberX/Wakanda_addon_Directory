#include "Jsonparser.h"
#include"curlcpp.h"
#include "rapidjson\document.h"
using namespace rapidjson;
#include<string>
#include<vector>
using namespace std;

namespace WaDirectory_data
{
	Jsonparser::Jsonparser()
	{
	}


	Jsonparser::~Jsonparser()
	{
	}


	string Jsonparser::login(string Username, string Password)
	{

		curlcpp curltest;
		curltest.initall();
		this->cookie = curltest.login(Username, Password, "http://localhost:8081/rest/$directory/login");
		if (curltest.res != CURLE_OK)
			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;
		else {

			Document document;
			document.Parse(curltest.data.str.c_str());
			assert(document["result"].IsBool());
			if (document["result"].GetBool() == true)return (getWASID());
			if (document["result"].GetBool() == false)return "";
		}
		return "";
	}

	string Jsonparser::getWASID()
	{
		string sub = "";
		int pos = cookie.find("WASID	");
		sub = cookie.substr(pos + 6);
		
		return sub;
	}
	bool Jsonparser::Logout()
	{

		curlcpp curltest;
		curltest.initall();
		curltest.Logout("http://localhost:8081/rest/$directory/logout", this->cookie);
		this->cookie = "";
		if (curltest.res != CURLE_OK)
			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;
		else {

			Document document;
			document.Parse(curltest.data.str.c_str());
			assert(document["result"].IsBool());
			if (document["result"].GetBool() == true)return true;
			if (document["result"].GetBool() == false)return false;
		}
		return false;
	}


	bool Jsonparser::currentUserBelongsTo(string Idgroup, string Namegroup)
	{

		curlcpp curltest;
		curltest.initall();
		curltest.currentUserBelongsTo("http://localhost:8081/rest/$directory/currentUserBelongsTo", Idgroup, Namegroup, this->cookie);
		if (curltest.res != CURLE_OK)
			cerr << "ERROR: " << curl_easy_strerror(curltest.res) << endl;
		else {

			Document document;
			document.Parse(curltest.data.str.c_str());
			assert(document["result"].IsBool());
			if (document["result"].GetBool() == true)return true;
			if (document["result"].GetBool() == false)return false;
		}
		return false;
	}


	vector<std::string> Jsonparser::currentuser()
	{
		std::vector<std::string> resultat;
		curlcpp curltest;
		curltest.initall();
		curltest.curentuser("http://localhost:8081/rest/$directory/currentUser", this->cookie);
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

				for (Value::ConstMemberIterator itr = document["result"].MemberBegin();
					itr != document["result"].MemberEnd(); ++itr)
				{
					if (itr->name == "userName") {
						resultat.push_back(itr->value.GetString());
					}
					if (itr->name == "fullName") {
						resultat.push_back(itr->value.GetString());
					}
					if (itr->name == "ID") {
						resultat.push_back(itr->value.GetString());
					}

				}

			}

		}
		return resultat;
		return vector<std::string>();
	}
}