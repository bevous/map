#include "map.h"
#include<string>
#include <iostream>
#include <fstream>

/**
 *
 */
std::string get_name(std::string file_path) {
	std::ifstream in_file;
	in_file.open(file_path);
	static std::string last_name_used="";
	std::string buffer = "";
	while (buffer!=last_name_used && !in_file.eof())
	{
		std::getline(in_file,buffer);
	}
	std::getline(in_file, last_name_used);
	in_file.close();
	return last_name_used;
}
// change this for your system.
const std::string filePath = "Test.csv";

const int target_size = 50;


int main()
{
	std::cout << filePath << std::endl;
	
	std::cout << "working" << std::endl;
	nwacc::map<std::string, int> my_tree;
	int key_for_later = 0;
	while (my_tree.size() < target_size)
	{
		auto id = std::rand();
		if (!my_tree.contains_key(id)) {
			if(key_for_later<id)
			{
				key_for_later = id;
			}
			auto test = my_tree.insert(get_name(filePath), id);
		}
	}
	std::cout << "------------" << std::endl << std::endl;

	for (nwacc::map<std::string, int>::iterator current_item = my_tree.first(); current_item != my_tree.end(); current_item++)
	{
		std::cout << /*current_item.get_info()*/ *current_item <<std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (nwacc::map<std::string, int>::iterator current_item = my_tree.last(); current_item != my_tree.begin(); current_item--)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "testing the operators." << std::endl << std::endl;

	nwacc::map<std::string, int> new_map = my_tree;
	std::cout<< *new_map[key_for_later] <<std::endl;
	std::cout << "------------" << std::endl << std::endl;
	std::cout << (*new_map[key_for_later] = "john") << std::endl;
	std::cout << "------------" << std::endl << std::endl;
	for (nwacc::map<std::string, int>::iterator current_item = new_map.first(); current_item != new_map.end(); current_item++)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "------------" << std::endl << std::endl;
	for (nwacc::map<std::string, int>::iterator current_item = new_map.last(); current_item != new_map.begin(); current_item--)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "------------" << std::endl << std::endl;
	std::cout << new_map << std::endl;

	system("pause");
	return 0;
}