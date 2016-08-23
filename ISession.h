/*
    @file   ISession.h
    @abstract   define a session in Wakanda Directory
*/

#ifndef ISession_H
#define ISession_H
#include<string>
#include<vector>
using namespace std;

// namespace std 
// {
    // class string;
    // class vector; 
// }


namespace WaDirectory
{

    class IDirectory;
    class IUser;

    class ISession
    {
            public:

                virtual    IUser*  GetUser()                    =0;
                
                virtual     void GetWASID( std::string& outWASID) const           =0;

                virtual     IDirectory* GetDirectory() const        =0;

                virtual     bool    IsValid()                       =0;

                virtual     void LogOut()                                =0;
				virtual ~ISession(){};
				ISession(){};



    };

}
#endif