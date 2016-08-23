#include "Group.h"
#include"User.h"
#include"XMLparser.h"
using namespace WaDirectory_data;
namespace WaDirectory
{
	Directory* Group::GetDirectory() const
	{
		return this->Pt_Directory;

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
	void  Group::Set_Directory(Directory* Pt_Directory)
	{
		this->Pt_Directory = Pt_Directory;

	}

	void Group::GetName(string& ouName)
	{
		XMLparser PtparseurXml(this->Pt_Directory->Get_Url_Directory());
	
		ouName = PtparseurXml.NameGrouoById(this->Idgroup);
	}


	User* Group::GetUserByName(const std::string&  Username)
	{
		XMLparser PtparseurXml(this->Pt_Directory->Get_Url_Directory());
		
		User *usr;
		
		if (PtparseurXml.NameUserById(Username, "name").length()>0)
		
			usr = new User(Username, PtparseurXml.NameUserById(Username, "name"), PtparseurXml.NameUserById(Username, "fullname"), "");
		
		return usr;
	}


	void Group::GetSubGroupName(vector<string>& ouSubGroupNames)
	{
		ouSubGroupNames.clear();
		
		XMLparser PtparseurXml(this->Pt_Directory->Get_Url_Directory());
		
		ouSubGroupNames = PtparseurXml.ListGroupInclude(this->Idgroup);
	}
}