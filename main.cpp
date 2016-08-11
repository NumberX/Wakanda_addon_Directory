#pragma warning(disable:4996)
#include <iostream>
#include"Jsonparser.h"
#include"Directory.h"
#include"User.h"
#include"XMLparser.h"
using namespace WaDirectory;
using namespace WaDirectory_data;
using namespace std;

int main() {

	int x;
	Jsonparser test;
	string resultatlogin = test.login("Mohammed", "12345678");
	std::cout << "resultat login :" << resultatlogin << endl;
	bool resultatbelong = test.currentUserBelongsTo("", "newGroup1");
	std::cout << "resultat belong 1 :" << resultatbelong << endl;
	bool resultatlogout = test.Logout();
	std::cout << "resultat logout  :" << resultatlogout << endl;
	resultatbelong = test.currentUserBelongsTo("", "newGroup1");
	std::cout << "resultat belong 2 :" << resultatbelong << endl;
	resultatlogin = test.login("Mohammed", "12345678");
	std::cout << "resultat login :" << resultatlogin << endl;
	vector<string> resultatcurent = test.currentuser();
	std::cout << "Debut du resultat currentuser test 1" << endl;
	for (int i = 0; i < resultatcurent.size() ; i++)
		std::cout << resultatcurent[i] << endl;
	std::cout << "Fin du resultat currentuser" << endl;
	//resultatlogout = test.Logout();
	std::cout << "resultat logout 2 :" << resultatlogout << endl;
	resultatcurent = test.currentuser();
	std::cout << "Debut du resultat currentuser test 2" << endl;
	for (int i = 0; i < resultatcurent.size(); i++)
		std::cout << resultatcurent[i] << endl;
	std::cout << "Fin du resultat currentuser" << endl;
	WaDirectory::Directory d1;
	WaDirectory::User user("Mohammed", "", "1234555555","12345678");
	string str;
	user.GetName(str);
	std::cout << "Teste User" + str<<endl;
	bool resultat = user.BelongsToGroup("newGroup");
	std::cout<<"  resultat Belong user"<<resultat  <<endl;
	std::cout << "Teste Parser user"<< endl;
	XMLparser parser;
	string resultat1 = parser.NameUserById("0160CF950BE88D48B15EDCB6D62D5C0E","name");
	std::cout << "  Fin test parser" << resultat1 << endl;
	std::cout << "Teste Parser group " << endl;

	resultat1 = parser.NameGrouoById("E4D3A48D63A6964BB2939DC594E6B379");
	std::cout << "  Fin test parser" << resultat1 << endl;
	std::cout << "Teste List group " << endl;

	vector<string> resultat2 = parser.ListGroup();
	for (int i = 0; i < resultat2.size();i++)
	{ 
		std::cout << "ID" << resultat2[i] << endl;
		std::cout << "Name" << parser.NameGrouoById(resultat2[i]) << endl;
	
	}
	
	std::cout << "  Fin test List parser" << endl;
	std::cout << "  Debut test List parser Include" << endl;
	vector<string> resultat3 = parser.ListGroupInclude("609AEC500800264DA73D02932FF3648F");

	for (int i = 0; i < resultat3.size(); i++)
	{
		std::cout << "ID :" << resultat3[i] << endl;
		std::cout << "Name :" << parser.NameGrouoById(resultat3[i]) << endl;

	}

	std::cout << "  Fin test List parser Include" <<endl;


	std::cin >> x;
	return 0;
}