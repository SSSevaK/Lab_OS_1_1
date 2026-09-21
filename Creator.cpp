#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

struct employee
{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
		{
			throw " not correct argc";
		}
		std::string MyString = argv[1];
		int records = std::atoi(argv[2]);
		std::ofstream out(MyString, std::ios::binary);
		if (!out.is_open())
		{
			throw "file not open";
		}
		for (size_t i = 1; i <= records; ++i)
		{
			employee temp;
			std::cout << "it's " << i << '\n';
			std::cout << "input ID ";
			if (!(std::cin >> temp.num))
			{
				throw "not int";
			}
			std::cout << "input name < 10 ";
			if (!(std::cin >> temp.name))
			{
				throw "size > 10";
			}
			std::cout << "input Hours ";
			if (!(std::cin >> temp.hours))
			{
				throw "not int";
			}
			out.write(reinterpret_cast<const char*>(&temp), sizeof(employee));
		}
		out.close();
	}
	catch (const char* msq)
	{
		std::cout << msq;
	}
}