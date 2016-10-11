#ifndef SessionLog_H
#define SessionLog_H
#include<string>
using namespace std;

namespace WaDirectory_Data
{

	class SessionLog{
public:
	string OperationTime;
	
	string TypeOperation;
	
	string wsid;
	
	string IdUser;
	
	string NameUser;

	void affiche();

	SessionLog(){};
	
	~SessionLog(){};
};

}
#endif