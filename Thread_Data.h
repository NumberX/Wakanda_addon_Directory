#ifndef Thread_Data_H
#define Thread_Data_H
#include"v8.h"
#include"Session.h"
#include<string.h>
#include<vector>
using namespace v8;
using namespace std;
namespace WaDirectory_View {
	class Sessionwrap;
	class Userwrap;
	class Groupwrap;
	class Directorywrap;
	union Data
	{
		
		char* user ;

		char* password ;

		char* GroupId;

		char* SessionId;

		char*  Resultat_string;

		Directorywrap* PtDirectorywrap;
		
		Userwrap* PtUserwrap;

		Sessionwrap* ptSessionwrap;

		Groupwrap* PtGroupWrap;
		
		ISession *PtSession;

		IGroup *PtGroup;

		IUser *Ptuser;

		bool Resultat;

		Data(){};

		

	};

	class Thread_Data
	{
	public:
		Thread_Data(){};

		~Thread_Data(){};

		string resultat;

		bool resultatvalid;

		Data Argument;

	};
	}
#endif