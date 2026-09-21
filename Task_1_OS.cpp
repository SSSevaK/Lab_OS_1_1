#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

struct employee 
{
    int num;
    char name[10];
    double hours;
};
bool RunProcess(const std::string& cmdLine) 
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::string cmdLinecopy = cmdLine;

    BOOL created = CreateProcessA(NULL, &cmdLinecopy[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (!created)
    {
        std::cout << "Failed to start process: " << cmdLine << "\n";
        return false;
    }   
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

void PrintBinaryFile(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Failed to read binary file: " << filename << "\n";
        return;
    }

    std::cout << filename << "\n";
    employee temp;
    while (in.read(reinterpret_cast<char*>(&temp), sizeof(employee)))
    {
        std::cout << "ID: " << temp.num << " | Name: " << temp.name << " | Hours: " << temp.hours << "\n";
    }
}

void PrintReportFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) 
    {
        std::cout << "Failed to read report file: " << filename << "\n";
        return;
    }

    std::cout << filename << '\n';
    std::string line;
    while (std::getline(in, line)) 
    {
        std::cout << line << "\n";
    }
}

int main()
{
    std::string binFileName;
    int recordCount;
    std::cout << "Enter binary file name: ";
    std::cin >> binFileName;
    std::cout << "Enter number of records: ";
    std::cin >> recordCount;
    std::string creatorCmd = "Creator.exe " + binFileName + " " + std::to_string(recordCount);
    std::cout << "\nLaunching Creator process...\n";
    if (!RunProcess(creatorCmd))
    {
        return 1;
    }
    PrintBinaryFile(binFileName);
    std::string reportFileName;
    double Rate;
    std::cout << "Enter report file name: ";
    std::cin >> reportFileName;
    std::cout << "Enter pay per hour: ";
    std::cin >> Rate;
    std::string reporterCmd = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(Rate);
    std::cout << "\nLaunching Reporter process...\n";
    if (!RunProcess(reporterCmd))
    {
        return 1;
    }
    PrintReportFile(reportFileName);
    std::cout << "Main program finished successfully.\n";
    return 0;
}