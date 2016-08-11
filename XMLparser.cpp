#include "XMLparser.h"
#include"rapidxml/rapidxml.hpp"
#include<fstream>
#include<sstream>
#include<iostream>
using namespace rapidxml;
namespace WaDirectory_data
{
	XMLparser::XMLparser()
	{
	}


	XMLparser::~XMLparser()
	{
	}


	string XMLparser::NameUserById(string Id, string attribut)
	{
		std::ifstream file("C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

			rapidxml::xml_document<> xml;
			xml.parse<0>((char*)&content[0]);

			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return "";


			for (rapidxml::xml_node<> * node = root_node->first_node("user"); node; node = node->next_sibling("user")) {
				//std::cout << "Found node: " << node->name() << std::endl;

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				rapidxml::xml_attribute<> * name_attribute = node->first_attribute("name");
				rapidxml::xml_attribute<> * fullName_attribute = node->first_attribute("fullName");
				if (ID_attribute != 0)
				{
					if (attribut == "name")

					{
						if (name_attribute != 0)
		                    
							if (ID_attribute->value() == Id)
							{
								
								return name_attribute->value();
							}

					}
					if (attribut == "fullName")

					{
						if (fullName_attribute != 0)
							if (ID_attribute->value() == Id)
							{
							
								return fullName_attribute->value();
							}

					}
				}

			}
		}

		return "";
	}


	string XMLparser::NameGrouoById(string Id)
	{
		std::ifstream file("C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

			rapidxml::xml_document<> xml;
			xml.parse<0>((char*)&content[0]);

			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return "";


			for (rapidxml::xml_node<> * node = root_node->first_node("group"); node; node = node->next_sibling("group")) {
				//std::cout << "Found node: " << node->name() << std::endl;

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				rapidxml::xml_attribute<> * name_attribute = node->first_attribute("name");
				if (ID_attribute != 0)
				{
					if (ID_attribute->value() == Id)
						
						return name_attribute->value();

				}
			}
		}

		return "";
	}


	vector<string> XMLparser::ListGroup()
	{
		std::vector<string> resultat;
		std::ifstream file("C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

			rapidxml::xml_document<> xml;
			xml.parse<0>((char*)&content[0]);

			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return resultat;


			for (rapidxml::xml_node<> * node = root_node->first_node("group"); node; node = node->next_sibling("group")) {

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				if (ID_attribute != 0)
				{
					rapidxml::xml_attribute<> * Name_attribute = node->first_attribute("name");
					resultat.push_back(Name_attribute->value());
				}
			}
		}

		return resultat;
	}


	vector<string> XMLparser::ListGroupInclude(string Id)
	{


		std::vector<string> resultat;
		std::ifstream file("C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

			rapidxml::xml_document<> xml;
			xml.parse<0>((char*)&content[0]);

			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return resultat;


			for (rapidxml::xml_node<> * node = root_node->first_node("group"); node; node = node->next_sibling("group")) {

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				if (ID_attribute != 0)
				{

					//resultat.push_back(ID_attribute->value());
					if (ID_attribute->value() == Id)
					{
						

						for (rapidxml::xml_node<> * node1 = node->first_node("include"); node1; node1 = node1->next_sibling("include")) {
							rapidxml::xml_attribute<> * grpId = node1->first_attribute("id");

							rapidxml::xml_attribute<> * pt = node1->first_attribute();

							string group = "group";
							if (pt->name() == group)
							{

								rapidxml::xml_attribute<> * groupID = pt->next_attribute();
								if (groupID != 0)
								{
									resultat.push_back(groupID->value());
								}

							}
						}

					}
				}
			}

			return resultat;

		}

	}



	bool WaDirectory_data::XMLparser::UserBelongGroup(string UserId, string groupId)
	{


		std::ifstream file("C:/Users/user/Documents/Wakanda/Untitled/Untitled Solution/directory.waDirectory");
		std::stringstream buffer;

		if (file) {
			buffer << file.rdbuf();
			file.close();

			std::string content = buffer.str();

			rapidxml::xml_document<> xml;
			xml.parse<0>((char*)&content[0]);

			rapidxml::xml_node<> * root_node = xml.first_node("directory");
			if (root_node == 0) return false;


			for (rapidxml::xml_node<> * node = root_node->first_node("group"); node; node = node->next_sibling("group")) {

				rapidxml::xml_attribute<> * ID_attribute = node->first_attribute("ID");
				if (ID_attribute != 0)
				{

					//resultat.push_back(ID_attribute->value());
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

		

		}

		return false;
	}
}