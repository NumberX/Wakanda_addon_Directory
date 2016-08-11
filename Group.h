/*
@file IGroup.h
@abstract   Group definition
*/


#pragma once
#include<vector>
#include<string>
using namespace std;


namespace WaDirectory
{


	class Directory;
	class User;

	class Group
	{
	public:
		string Idgroup, Namegroup;
		Group();
		~Group();
		Group(string id);
		void   GetName(string& outName) ;

		User* GetUserByName(string& inUserName) ;

		void GetSubGroupName(std::vector<std::string>& ouSubGroupNames) ;
		    
		Directory* GetDirectory() const ;
	};



}