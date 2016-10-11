/*
@file IGroup.h
@abstract   Group definition
*/


#ifndef Group_H
#define Group_H
#include"IGroup.h"
#include"Directory.h"
#include"User.h"
#include<vector>
#include<string>
using namespace std;


namespace WaDirectory_Data
{


	class Directory;
	class User;

	class Group:public IGroup
	{
		
	public:
		
		Group();
		 ~Group();
		Group(string id);
		 void   GetName(std::string& outName);

		 void GetId(string& ouName);

		 IUser* GetUserByName(const std::string& inUserName, const std::string& Password);

		 void GetSubGroupName(std::vector<std::string>& ouSubGroupNames);

		 void GetSubGroupId(vector<string>& ouSubGroupNames);
		 
		 void Getuserinclude(vector<string>& ouSubGroupNames);

		 IDirectory* GetDirectory() ;
		 void Set_Directory(IDirectory* Pt_Directory);


	};



}
#endif