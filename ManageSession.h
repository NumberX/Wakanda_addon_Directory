#pragma once
#include"UnionUserSession.h"
#include<vector>
namespace WaDirectory
{
	class ManageSession
	{
		
	public:
		vector<UnionUserSession> *list;

		ManageSession();

		~ManageSession();

		void Register(string IdUser, string cookies,string Username);

		bool FindByUserId(string IdUser);

		vector<UnionUserSession> getList();

		string Getcookies(string IdUser);

		void Remove(string IdUser);

		void RemoveBycookies(string cookies);

		void Affiche();
	};
}
