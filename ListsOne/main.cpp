#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "ForwardList.h"
#include "Pair.h"
#include "CommandExecutor.h"

int main(int argc, char* argv[])
{
    std::ifstream fileInput;

    if (argc != 2)
    {
        std::cout << "Error" << std::endl;
    }

    //fileInput.open(argv[1]);
    fileInput.open("a.txt");

    if (!fileInput.is_open())
    {
        std::cerr << "The input file was not opened.";
        return 1;
    }

    /*dictionary< int, int > temp("Name");
    temp.push(1, 3);
    temp.push(2, 4);
    std::cout << temp << std::endl;*/

    CommandExecutor().run(fileInput);
}
