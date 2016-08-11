#pragma once
#include<string>
#include<vector>
using namespace std;
namespace WaDirectory_data
{
	class XMLparser
	{
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

