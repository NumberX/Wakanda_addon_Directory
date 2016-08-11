/*
@file   ISession.h
@abstract   define a session in Wakanda Directory
*/

#pragma once

#include<vector>
#include<string>
using namespace std;


namespace WaDirectory
{

	class Directory;
	class User;

	class Session
	{
	public:
		Session();
		Session(string cookies);

		~Session();
		User*  GetUser() ;

		void GetWASID(std::string& outWASID) const ;

		Directory* GetDirectory() const ;

		bool    IsValid() ;

		void LogOut() ;
		string wsid, cookies;


	};

}

