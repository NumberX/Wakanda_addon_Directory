#include "XMLparser.h"
#include"rapidxml/rapidxml.hpp"
#include<fstream>
#include<sstream>
#include<iostream>
using namespace rapidxml;
namespace WaDirectory_data
{
	XMLparser::XMLparser(string UrlDirectory)
	{
		this->UrlDirectory = UrlDirectory;
		std::ifstream file(this->UrlDirectory);
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

		
			xml.parse<0>((char*)&content[0]);

		}
	}


	XMLparser::~XMLparser()
	{
	}

	string XMLparser::UserIdByname(string name)
	{

		rapidxml::xml_node<> * RootNode = xml.first_node("directory");

		if (RootNode == 0)
			return false;

		for (rapidxml::xml_node<> * Iterator = RootNode->first_node("user"); Iterator; Iterator = Iterator->next_sibling("user"))
		{

			rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");

			rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");


			if (IDAttribute != 0)
			{
				
					if (NameAttribute != 0)

						if (NameAttribute->value() == name)
						{

							return IDAttribute->value();
						}
				
			}
		}

		return "";
	}



	bool XMLparser::ExistUserByname(string name, string NameAttribut)
	{

		rapidxml::xml_node<> * RootNode = xml.first_node("directory");

		if (RootNode == 0)
			return false;

		for (rapidxml::xml_node<> * Iterator = RootNode->first_node("user"); Iterator; Iterator = Iterator->next_sibling("user"))
		{

			rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");

			rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");


			if (IDAttribute != 0)
			{
				if (NameAttribut == "name")

				{
					if (NameAttribute != 0)

						if (NameAttribute->value() == name)
						{

							return true;
						}
				}
			}
		}

		return false;
	}
	string XMLparser::NameUserById(string Id, string NameAttribut)
	{

			rapidxml::xml_node<> * RootNode = xml.first_node("directory");
		
			if (RootNode == 0)
				return "";

			for (rapidxml::xml_node<> * Iterator = RootNode->first_node("user"); Iterator; Iterator = Iterator->next_sibling("user")) 
			{
				
				rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");
				
				rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");
				
				rapidxml::xml_attribute<> * FullNameAttribute = Iterator->first_attribute("fullName");
				
				if (IDAttribute != 0)
				{
					if (NameAttribut == "name")

					{
						if (NameAttribute != 0)
		                    
							if (IDAttribute->value() == Id)
							{
								
								return NameAttribute->value();
							}

					}
					if (NameAttribut == "fullName")
					{
						if (FullNameAttribute != 0)
					
							if (IDAttribute->value() == Id)
							{
							
								return FullNameAttribute->value();
							}

					}
					if (NameAttribut == "ID")
					{
						if (FullNameAttribute != 0)

							if (IDAttribute->value() == Id)
							{

								return IDAttribute->value();
							}

					}
				}

			}
		
		return "";
	
	}


	string XMLparser::NameGrouoById(string Id)
	{
			rapidxml::xml_node<> * RootNode = xml.first_node("directory");
			
			if (RootNode == 0) return "";


			for (rapidxml::xml_node<> * Iterator = RootNode->first_node("group"); Iterator; Iterator = Iterator->next_sibling("group"))
			{
				

				rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");
				
				rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");
			
				if (IDAttribute != 0)
				{
					if (IDAttribute->value() == Id)
						
						return NameAttribute->value();

				}
			}
		

		return "";
	}


	vector<string> XMLparser::ListGroup()
	{
		std::vector<string> resultat;
		
			rapidxml::xml_node<> * RootNode = xml.first_node("directory");
			
			if (RootNode == 0) return resultat;


			for (rapidxml::xml_node<> * Iterator = RootNode->first_node("group"); Iterator; Iterator = Iterator->next_sibling("group")) {

				rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");
				if (IDAttribute != 0)
				{
					rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");
					resultat.push_back(NameAttribute->value());
				}
			}
		

		return resultat;
	}

	vector<string> XMLparser::ListGroupId()
	{
		std::vector<string> resultat;

		rapidxml::xml_node<> * RootNode = xml.first_node("directory");

		if (RootNode == 0) return resultat;


		for (rapidxml::xml_node<> * Iterator = RootNode->first_node("group"); Iterator; Iterator = Iterator->next_sibling("group")) {

			rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");
			if (IDAttribute != 0)
			{
				rapidxml::xml_attribute<> * NameAttribute = Iterator->first_attribute("name");
				resultat.push_back(IDAttribute->value());
			}
		}


		return resultat;
	}
	vector<string> XMLparser::ListGroupInclude(string Id)
	{


		std::vector<string> resultat;

		rapidxml::xml_node<> * RootNode = xml.first_node("directory");
		
		if (RootNode == 0) return resultat;


		for (rapidxml::xml_node<> * Iterator = RootNode->first_node("group"); Iterator; Iterator = Iterator->next_sibling("group")) 
		{

			rapidxml::xml_attribute<> * IDAttribute = Iterator->first_attribute("ID");
			
			if (IDAttribute != 0)
				{

					if (IDAttribute->value() == Id)
					{
						

						for (rapidxml::xml_node<> * IteratorInclude = Iterator->first_node("include"); IteratorInclude; IteratorInclude = IteratorInclude->next_sibling("include"))
						{
							
							rapidxml::xml_attribute<> * Ptattribute = IteratorInclude->first_attribute();

							string group = "group";
							
							if (Ptattribute->name() == group)
							{

								rapidxml::xml_attribute<> * GroupIDAttribute = Ptattribute->next_attribute();
							
								if (GroupIDAttribute != 0)
								{
									resultat.push_back(GroupIDAttribute->value());
								}

							}
						}

					}
				}
			}

		

		
		return resultat;
	}



	bool WaDirectory_data::XMLparser::UserBelongGroup(string UserId, string groupId)
	{


			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return false;


			for (rapidxml::xml_node<> * node = root_node->first_node("group"); node; node = node->next_sibling("group")) {

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				if (ID_attribute != 0)
				{

					
					if (ID_attribute->value() == groupId)
					{
						

						for (rapidxml::xml_node<> * node1 = node->first_node("include"); node1; node1 = node1->next_sibling("include")) {
							rapidxml::xml_attribute<> * grpId = node1->first_attribute("id");

							rapidxml::xml_attribute<> * pt = node1->first_attribute();

							string user = "user";
							if (pt->name() == user)
							{
								
								rapidxml::xml_attribute<> * userID = pt->next_attribute();
								if (userID != 0)
								{
									
									if (userID->value() == UserId)return true;
								}

							}
						}

					}
				}
			}

		

		

		return false;
	}
}