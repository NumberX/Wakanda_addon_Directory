#ifndef Thread_Data_H
#define Thread_Data_H
#include"Directorywrap.h"
#include"v8.h"
#include"DirectorywrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"UserwrapAsynchro.h"
#include"SessionwrapAsynchro.h"
#include"Session.h"
#include<string.h>
#include<vector>
using namespace v8;
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8 {
	union Data
	{
		
		char* user ;

		char* password ;

		char* GroupId;

		char* SessionId;

		char*  Resultat_string;

		DirectorywrapAsynchro* PtDirectorywrapAsynchro;
		
		Directorywrap* PtDirectorywrap;

		UserwrapAsynchro* PtUserwrapAsynchro;

		SessionwrapAsynchro* ptSessionwrapAsynchro;

		GroupwrapAsynchro* PtGroupWrapAsynchro;
		
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

		Data Argument;

		Local<Object> ObjectDirectoryWrap;
	};
	}
#endif