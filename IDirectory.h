/*
    @file IDirectory.h
    @abstract Directory interface definition
*/

#ifndef IDirectory_H
#define IDirectory_H
#include<string>
#include<vector>
using namespace std;

// namespace std
// {
    // class string;
    // template<>  class vector;

// }

namespace WaDirectory
{
    class IGroup;
    class IUser;
    class ISession;

    class IDirectory 
    {
        public:
         

            virtual ISession*    LogIn(const std::string& inUser, const std::string& inPassword) = 0;

            virtual void         GetGroupNames( std::vector<std::string>& outGroupName)               =0;

            virtual IGroup*      GetGroup (const std::string& inGroupName)                       =0;

            virtual IUser*       GetUser ( const std::string& inUserName)                        =0;

            virtual bool         LogOut( const ISession* inSession)                              =0;

            virtual ISession*    GetSession(const std::string& inSessionID)                         =0;

            virtual bool         UserBelongTo(const ISession* inSession, const std::string& inGroupID ) =0;

            virtual bool         UserBelongTo(const IUser* inUser, const std::string& inGroupID ) =0;

            virtual bool         UserBelongTo(const IUser* inUser, const IGroup* inGroupID ) =0;
			virtual ~IDirectory(){};
			IDirectory(){}

    };
}
#endif

