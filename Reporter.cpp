#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {

    try
    {
        if (argc < 4)
        {
            throw " argc < 4";
        }
        std::string MyString_i = argv[1];
        std::string MyString_o = argv[2];
        double price = std::atof(argv[3]); 
        std::ifstream input(MyString_i, std::ios::binary);
        std::ofstream out(MyString_o);
        if (!input.is_open())
        {
            throw " input not open";
        }
        if (!out.is_open())
        {
            throw " out not open";
        }
        out << MyString_i << "»\n";
        out << std::left << std::setw(15) << "num" << std::setw(15) << "name" << std::setw(15) << "hours" << std::setw(15) << "salary" << '\n';
        employee temp;
        while (input.read(reinterpret_cast<char*>(&temp), sizeof(employee)))
        {
            double salary = temp.hours * price;
            out << std::left << std::setw(15) << temp.num << std::setw(15) << temp.name << std::setw(15) << temp.hours << std::setw(15) << salary << '\n';
        }
        input.close();
        out.close();
    }
    catch (const char* msq)
    {
        std::cout << msq;
    }
}