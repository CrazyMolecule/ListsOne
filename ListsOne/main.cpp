#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "ForwardList.h"
#include "Pair.h"
#include "CommandExecutor.h"

int main(int argc, char* argv[])
{
    std::ifstream fileInput;

    fileInput.open(argv[1]);

    if (!fileInput.is_open())
    {
        std::cerr << "The input file was not opened.";
        return 1;
    }

    CommandExecutor().run(fileInput);
}
