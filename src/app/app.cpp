/*
 * app.cpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#include "app/app.hpp"
#include <iostream>
#include "commands/all.hpp"

namespace app
{

//------------------------------------------------------------------------------
Application::Ptr Application::create()
{
    return Ptr (new Application());
}

//------------------------------------------------------------------------------
void Application::run()
{
    while(std::cin)
    {
        ready();
        std::string line;
        std::getline(std::cin, line);
        Args args(line);
        std::string cmdName;
        args >> cmdName;
        if (not cmdName.empty())
        {
            auto kv = commands_.find(cmdName);
            if ( kv != commands_.end())
                kv->second->execute(args);
            else
                invalid();
        }
    }
}

//------------------------------------------------------------------------------
void Application::addCommands()
{
    commands_["lstab"] = dynamo::ListTables::Ptr(new dynamo::ListTables());
    // TODO:
}

//------------------------------------------------------------------------------
void Application::ready()
{
    std::cout /*<< std::endl*/ << "#";
}

//------------------------------------------------------------------------------
void Application::invalid()
{
    std::cout << "invalid" << std::endl;
}

} // app namespace

