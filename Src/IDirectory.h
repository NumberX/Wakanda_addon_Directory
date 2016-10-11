/*
    @file IDirectory.h
    @abstract Directory interface definition
*/

#ifndef IDirectory_H
#define IDirectory_H
#include<string>
#include<vector>
#include "XMLparser.h"
#include"ManageSession.h"
#include"SessionLog.h"
using namespace std;

// namespace std
// {
    // class string;
    // template<>  class vector;

// }

namespace WaDirectory_Data
{
    class IGroup;
    class IUser;
    class ISession;
	class ManageSession;

    class IDirectory 
    {
        public:
         
			

			virtual ISession*    LogIn(const std::string& inUser, const std::string& inPassword) = 0;

			virtual void         GetGroupNames(std::vector<std::string>& outGroupName) = 0;

			virtual IGroup*      GetGroup(const std::string& inGroupName) = 0;
			
			virtual IUser*       GetUser(const std::string& inUserName, const std::string& Password) =0;

			virtual bool         LogOut(const ISession* inSession) = 0;

			virtual ISession*    GetSession(const std::string& inSessionID) = 0;

			virtual bool         UserBelongTo(const ISession* inSession, const std::string& inGroupID)  = 0;

			virtual bool         UserBelongTo(const IUser* inUser, const std::string& inGroupID) = 0;

			virtual bool         UserBelongTo(const IUser* inUser, const IGroup* inGroupID)  = 0;

			virtual std::string	 Get_Url_Wakanda()  = 0;

			virtual std::string  Get_Url_Directory()  = 0;

			virtual void		 Set_Url_Wakanda(std::string Url_Wakanda) = 0;

			virtual void		 Set_Url_Directory(std::string Url_Directory) = 0;

			virtual bool         Existbyname(string name)  = 0;

			virtual bool         Isvalid(string Username, string Password) = 0;

			virtual IUser*		 GetUserById(const std::string& inUserId) = 0;

			virtual void        GetGroupId(std::vector<std::string>& outGroupName)=0;

			virtual void        GetUsersId(std::vector<std::string>& outGroupName) = 0;

			virtual vector<SessionLog> loadfile()=0;

			

		std::string Url_Wakanda, Url_Directory;

		ManageSession List;

    };
}
#endif

