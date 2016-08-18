#include "Group.h"
#include"User.h"
#include"XMLparser.h"
using namespace WaDirectory_data;
namespace WaDirectory
{
	Directory* Group::GetDirectory() const
	{
		return nullptr;

	}
	Group::Group() 
	{
	}

	Group::Group(string id)
	{
		this->Idgroup = id;
	}

	Group::~Group()
	{
	}


	void Group::GetName(string& ouName)
	{
		XMLparser prt;
		ouName=prt.NameGrouoById(this->Idgroup);
	}


	User* Group::GetUserByName(const std::string&  Username)
	{
		XMLparser prt;
		User *usr;
		if (prt.NameUserById(Username, "name").length()>0)
		usr = new User(Username,prt.NameUserById(Username, "name"), prt.NameUserById(Username, "fullname"),"");
		return usr;
	}


	void Group::GetSubGroupName(vector<string>& ouSubGroupNames)
	{
		ouSubGroupNames.clear();
		XMLparser prt;
		ouSubGroupNames = prt.ListGroupInclude(this->Idgroup);
	}
}