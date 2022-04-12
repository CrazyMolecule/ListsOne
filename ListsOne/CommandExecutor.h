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
        //TO DO: сделать friend class с этими всеми командами или нет?.. тогда как получить доступ к словарю со словарями (тому, что главный)?
        reg_command("print", print);
        reg_command("complement", complement);
        reg_command("intersect", intersect);
        reg_command("union", myunion);

        //MAYBE TO DO: m_Dictionaries;
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
                for (int i = 0; i < temp.getCount() / 2; i++)
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
                    operation(currentCommand.getArgs());
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
        if (!"главный словарь содержит все имена из аргументов")
        {
            throw std::invalid_argument("Invalid argument.");
        }

        std::cout << "По имени словаря из аргумента вывести норм словарь" << std::endl;
    }

    void complement(forward_list< std::string > args)
    {
    }

    void intersect(forward_list< std::string > args)
    {
    }

    void myunion(forward_list< std::string > args)
    {
    }

private:
    dictionary < std::string, void (CommandExecutor::*)(forward_list< std::string >) > m_RegisteredCommands;
    dictionary < std::string, dictionary < int, std::string > > m_Dictionaries;

    void reg_command(std::string command, void (CommandExecutor::* function)(forward_list< std::string >))
    {
        m_RegisteredCommands.push(command, function);
    }
};