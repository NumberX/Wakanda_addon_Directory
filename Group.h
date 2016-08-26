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


namespace WaDirectory
{


	class Directory;
	class User;

	class Group
	{
		Directory* Pt_Directory = NULL;
	public:
		string Idgroup, Namegroup;
		Group();
		~Group();
		Group(string id);
		void   GetName(std::string& outName);

		User* GetUserByName(const std::string& inUserName, const std::string& Password);

		void GetSubGroupName(std::vector<std::string>& ouSubGroupNames) ;
		    
		Directory* GetDirectory() const ;
		void Set_Directory(Directory* Pt_Directory);


	};



}
#endif