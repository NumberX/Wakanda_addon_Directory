#include "UnionUserSession.h"

namespace WaDirectory_Data
{
	UnionUserSession::UnionUserSession()
	{
		//this->MaxAgeTtl = new double();
	}


	UnionUserSession::~UnionUserSession()
	{
	}
	string UnionUserSession::getWASID()
	{
		
			string sub = "";

			int pos = static_cast<int>(this->cookies.find("WASID	"));

			sub = this->cookies.substr(pos + 6);

			return sub;

		
	}

}