#pragma once
#include "XMLparser.h"
#include"rapidxml/rapidxml.hpp"
#include<string>
#include<vector>
using namespace rapidxml;
using namespace std;
namespace WaDirectory_data
{
	class XMLparser
	{
		rapidxml::xml_document<> xml;
	public:
		XMLparser();
		~XMLparser();
		string NameUserById(string Id, string attribut);
		string NameGrouoById(string Id);
		vector<string> ListGroup();
		vector<string> ListGroupInclude(string Id);
		bool UserBelongGroup(string UserId, string groupId);
	};
}

