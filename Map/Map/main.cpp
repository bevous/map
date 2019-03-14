#include "avl_tree.h"
#include<string>
#include <fstream>
std::string get_name(std::string file_path) {
	std::ifstream in_file(file_path);
	static std::string last_name_used="";
	std::string buffer = "";
	while (true)
	{

	}

}
int get_id_number(std::string file_path) {

}

// change this for your system.
const std::string filePath = "C:\\Users\\nomad\\source\\repos\\map4\\Test.csv";

int main()
{
	std::cout << filePath << std::endl;
	
	
	int numbers[8] = { 1,2,5,8,4,5,15,20 };
	std::cout << "working" << std::endl;
	nwacc::avl_tree<std::string, int> my_tree;
	int x = 0;
	while (x < 8)
	{
		my_tree.insert(get_name(filePath), get_id_number(filePath));
		x++;
	}
	std::cout << "there are no problems inserting" << std::endl;

	for (nwacc::avl_tree<std::string, int>::iterator current_item = my_tree.begin(); current_item != my_tree.end(); current_item++)
	{
		std::cout << *current_item << ", ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (nwacc::avl_tree<std::string, int>::iterator current_item = my_tree.end(); current_item != my_tree.begin(); current_item--)
	{
		std::cout << *current_item << ", ";
	}

	system("pause");
	return 0;
}