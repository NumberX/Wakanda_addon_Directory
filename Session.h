/*
@file   ISession.h
@abstract   define a session in Wakanda Directory
*/

#ifndef Session_H
#define Session_H
#include"ISession.h"
#include<vector>
#include<string>
using namespace std;


namespace WaDirectory
{

	class Directory;
	class User;

	class Session 
	{
		Directory* Pt_Directory = NULL;

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

		void Set_Directory(Directory* Pt_Directory);

	};

}
#endif