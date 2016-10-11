#pragma once
#include "XMLparser.h"
#include"rapidxml/rapidxml.hpp"
#include<string>
#include<vector>
using namespace rapidxml;
using namespace std;
namespace WaDirectory_Data
{
	class XMLparser
	{
		rapidxml::xml_document<> xml;
		string UrlDirectory = "";
	public:
		XMLparser(string UrlDirectory);
		XMLparser();
		~XMLparser();
		void setUrl(string UrlDirectory);
		string NameUserById(string Id, string attribut);
		string NameGrouoById(string Id);
		vector<string> ListGroup();
		vector<string> ListGroupId();
		vector<string> ListUsersId();
		vector<string> ListGroupInclude(string Id);
		bool UserBelongGroup(string UserId, string groupId);
		bool ExistUserByname(string name, string NameAttribut);
		string UserIdByname(string name);
		vector<string> ListGroupIncludeId(string Id);
		vector<string> ListuserInclude(string Id);
	};
}

