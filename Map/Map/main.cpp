#include "avl_tree.h"
#include<string>
#include <fstream>
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

int main()
{
	std::cout << filePath << std::endl;
	
	int numbers[8] = { 1,2,5,8,4,5,15,20 };
	std::cout << "working" << std::endl;
	nwacc::avl_tree<std::string, int> my_tree;
	int x = 0;
	while (x < 50)
	{

		auto test = my_tree.insert(get_name(filePath), x);
		x++;
	}
	std::cout << "------------" << std::endl << std::endl;

	for (nwacc::avl_tree<std::string, int>::iterator current_item = my_tree.first(); current_item != my_tree.end(); current_item++)
	{
		std::cout << /*current_item.get_info()*/ *current_item <<std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (nwacc::avl_tree<std::string, int>::iterator current_item = my_tree.last(); current_item != my_tree.begin(); current_item--)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "testing the operators." << std::endl << std::endl;

	nwacc::avl_tree<std::string, int> new_map = my_tree;
	std::cout<< *new_map[45] <<std::endl;
	std::cout << "------------" << std::endl << std::endl;
	std::cout << (*new_map[45] = "john") << std::endl;
	std::cout << "------------" << std::endl << std::endl;
	for (nwacc::avl_tree<std::string, int>::iterator current_item = new_map.first(); current_item != new_map.end(); current_item++)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "------------" << std::endl << std::endl;
	for (nwacc::avl_tree<std::string, int>::iterator current_item = new_map.last(); current_item != new_map.begin(); current_item--)
	{
		std::cout << /*current_item.get_info()*/ *current_item << std::endl;
	}
	std::cout << "------------" << std::endl << std::endl;
	std::cout << new_map << std::endl;


	system("pause");
	return 0;
}