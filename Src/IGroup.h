/*
    @file IGroup.h
    @abstract   Group definition
*/


#ifndef IGroup_H
#define IGroup_H
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


    class IDirectory;
    class IUser;

    class IGroup
    {
		
	public:
		string Idgroup, Namegroup;

		virtual  void   GetName(std::string& outName)  = 0;

		virtual  IUser* GetUserByName(const std::string& inUserName, const std::string& Password)  = 0;

		virtual  void GetSubGroupName(std::vector<std::string>& ouSubGroupNames) = 0;
            
        virtual  IDirectory* GetDirectory()                                   =0;

		virtual void Set_Directory(IDirectory* Pt_Directory)				= 0;

		virtual void GetId(string& ouName) = 0;

		virtual void GetSubGroupId(vector<string>& ouSubGroupNames) = 0;

		virtual void Getuserinclude(vector<string>& ouSubGroupNames) = 0;
		
		IDirectory* Pt_Directory = NULL;
	
    };



}
#endif