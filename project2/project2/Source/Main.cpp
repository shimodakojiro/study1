
#include<iostream>
#include<fstream>
#include<list>
#include<iterator>

#include"../Header/FileData.h"
#include"../Header/Main.h"

void main()
{
	std::ifstream ifs("../Test.txt");
	if (ifs.fail()){
		std::cerr << "“Ç‚Ýž‚Ý‚ÉŽ¸”s" << std::endl;
		return;
	}


	char str[100];
	ifs.getline(str, 99);
//	std::cout << str << std::endl;


	std::list<CFileData>filedata;
	std::list<CFileData>::iterator itr;

	filedata.push_back(CFileData());
	itr = filedata.begin();

	itr->SetFileData(str, 2);

	std::cout << itr->GetName() << std::endl;
	
}
