#pragma once

#include <iostream>
#include <string>
#include "Dictionary.h"
#include "Command.h"
#include <functional>
#include "ForwardList.h"

class CommandExecutor
{
public:
    CommandExecutor()
    {
        reg_command("print", &CommandExecutor::print);
        reg_command("complement", &CommandExecutor::complement);
        reg_command("intersect", &CommandExecutor::intersect);
        reg_command("union", &CommandExecutor::myUnion);
    }

    void readFile(std::istream& input)
    {
        std::string line = "";
        while (getline(input, line))
        {
            if (!line.empty())
            {
                forward_list< std::string > data = splitString(line, " ");
                std::string dictName = data[0];
                dictionary< int, std::string > temp(dictName);
                data.popFront();
                while (data.getCount() > 0)
                {
                    temp.push(std::stoi(data[0]), data[1]);
                    data.popFront();
                    data.popFront();
                }
                m_Dictionaries.push(dictName, temp);
            }
        }
    }

    void run(std::istream& input)
    {
        readFile(input);

        std::string line = "";
        while (getline(std::cin, line))
        {
            if (!line.empty())
            {
                Command currentCommand(line);
                if (m_RegisteredCommands.has(currentCommand.getOperation()))
                {
                    void (CommandExecutor:: * operation)(forward_list< std::string >);
                    operation = m_RegisteredCommands[currentCommand.getOperation()];
                    forward_list< std::string > args = currentCommand.getArgs();
                    (this->*operation)(args);
                }
            }
        }
    }

    void print(forward_list< std::string > args)
    {
        if (args.getCount() != 1)
        {
            throw std::length_error("Invalid number of command arguments.");
        }
        if (!m_Dictionaries.has(args[0]))
        {
            throw std::invalid_argument("Invalid argument.");
        }

        dictionary < int, std::string > toPrint = m_Dictionaries[args[0]];
        std::cout << toPrint << std::endl;
    }

    void complement(forward_list< std::string > args)
    {

    }

    void intersect(forward_list< std::string > args)
    {
    }

    void myUnion(forward_list< std::string > args)
    {
        std::string newDataSet = args[0];
        std::string dataSetOne = args[1];
        std::string dataSetTwo = args[2];

        dictionary< int, std::string > temp(newDataSet);
        temp = m_Dictionaries[dataSetOne];
        temp.getUnion(m_Dictionaries[dataSetTwo]);

        m_Dictionaries.push(newDataSet, temp);
    }

private:
    dictionary < std::string, void (CommandExecutor::*)(forward_list< std::string >) > m_RegisteredCommands;
    dictionary < std::string, dictionary < int, std::string > > m_Dictionaries;

    void reg_command(std::string command, void (CommandExecutor::* function)(forward_list< std::string >))
    {
        m_RegisteredCommands.push(command, function);
    }
};