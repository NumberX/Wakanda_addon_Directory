/*
    @file   IUser.h
    @abstract   define the user object interface
*/

#ifndef IUser_H
#define IUser_H
#include"IDirectory.h"
#include<string>
#include<vector>
using namespace std;
// namespace std 
// {
    // class string;
    // class vector; 
// }

namespace WaDirectory_Data
{


    class IUser
    {
	private:

		

	public:
		string Username, FullName, Id, Password;
    
            virtual  IDirectory* GetDirectory()             =0;
            
			virtual void    GetName(std::string& outName)   = 0;

			virtual bool    BelongsToGroup(const std::string& inGroupName) = 0;

			virtual bool    BelongsToGroup(const IGroup* inGroupName)  = 0;

			virtual bool    IsLoggedIn(const ISession* inSession) = 0;


			virtual void Set_Directory(IDirectory* Pt_Directory) = 0;

			IDirectory *Pt_Directory = NULL;

			

    };
    
}
#endif