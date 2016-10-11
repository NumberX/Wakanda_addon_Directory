#pragma once
#include"UnionUserSession.h"

#include<vector>
namespace WaDirectory_Data
{
	class IDirectory;
	class ManageSession
	{
		
	public:
		vector<UnionUserSession> list;

		ManageSession();

		~ManageSession();

		void Register(string IdUser, string cookies, string Username, double InputTtl);

		bool FindByUserId(string IdUser);

		bool findcookiesbywsid(string& wsid);

		vector<UnionUserSession> getList();

		string Getcookies(string IdUser);

		string GetUserId(string cookies);

		void Remove(string IdUser);

		void RemoveBycookies(string cookies);

		void UpdateBycookies(string cookies,  double InputTtl);

		void Affiche();

		void SaveOperation(time_t OperationTime, string TypeOperation, string wsid, string IdUser, string NameUser);

		void Task(int TimeSleep,IDirectory* Pt_Directory,vector<UnionUserSession> & list);
	};
}
