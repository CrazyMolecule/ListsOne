#pragma once

#include "Utils.h"

class Command
{
public:
    Command(const std::string& raw_command)
    {
        forward_list< std::string > entries = splitString(raw_command, " ");

        if (entries.getCount() < 2)
        {
            throw std::invalid_argument("String '" + raw_command + "' cannot be used as a command.");
        }

        m_Operation = entries[0];
        entries.popFront();
        m_Args = entries;
    }

    std::string getOperation() const
    {
        return m_Operation;
    }

    forward_list< std::string > getArgs() const
    {
        return m_Args;
    }

private:
    std::string m_Operation;
    forward_list< std::string > m_Args;
};