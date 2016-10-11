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


namespace WaDirectory_Data
{

	class Directory;
	class User;

	class Session :public ISession
	{
		

	public:
		Session();
		Session(string cookies);

		~Session();
		 IUser*  GetUser();

		 void GetWASID(std::string& outWASID) ;

		 IDirectory* GetDirectory() ;

		 bool    IsValid();

		 void LogOut();
		
		
		 void GetWASID1(std::string& outWASID);
		 void Set_Directory(IDirectory* Pt_Directory);

	};

}
#endif