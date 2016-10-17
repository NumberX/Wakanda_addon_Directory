#include "Group.h"
#include"User.h"
#include"XMLparser.h"
#include<iostream>
using namespace std;
namespace WaDirectory_Data
{
	IDirectory* Group::GetDirectory() 
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
	void  Group::Set_Directory(IDirectory* Pt_Directory)
	{
		this->Pt_Directory = Pt_Directory;

	}

	void Group::GetName(string& ouName)
	{
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Pt_Directory->Get_Url_Directory());

		ouName = PtparseurXml->NameGrouoById(this->Idgroup);

		delete PtparseurXml;
	}
	void Group::GetId(string& ouName)
	{
		

		ouName = this->Idgroup;
	}
	
	IUser* Group::GetUserByName(const std::string&  Username, const std::string& Password)
	{
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Pt_Directory->Get_Url_Directory());

		User *usr;
		if (PtparseurXml->ExistUserByname(Username, "name"))
		{
			

			string Id = PtparseurXml->UserIdByname(Username);
		
			if (PtparseurXml->NameUserById(Id, "name").length()>0)

				usr = new User(Username, PtparseurXml->NameUserById(Id, "fullname"), PtparseurXml->NameUserById(Id, "ID"), Password);


		}
		
		delete PtparseurXml;

		return usr;
	}

	void Group::GetSubGroupId(vector<string>& ouSubGroupNames)
	{
		ouSubGroupNames.clear();

		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Pt_Directory->Get_Url_Directory());

		ouSubGroupNames = PtparseurXml->ListGroupIncludeId(this->Idgroup);

		delete PtparseurXml;
	}
	void Group::GetSubGroupName(vector<string>& ouSubGroupNames)
	{
		ouSubGroupNames.clear();
		
		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Pt_Directory->Get_Url_Directory());

		ouSubGroupNames = PtparseurXml->ListGroupInclude(this->Idgroup);

		delete PtparseurXml;
	}

	void Group::Getuserinclude(vector<string>& ouSubGroupNames)
	{
		ouSubGroupNames.clear();

		XMLparser *PtparseurXml;

		PtparseurXml = new XMLparser(this->Pt_Directory->Get_Url_Directory());

		ouSubGroupNames = PtparseurXml->ListGroupIncludeId(this->Idgroup);

		delete PtparseurXml;
	}
}