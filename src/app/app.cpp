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
            {
                kv->second->execute(args);
            }
            else if (cmdName == "help")
            {
                for (auto& kv : commands_)
                    std::cout << kv.first << std::endl;
            }
            else if (cmdName == "exit")
                break; // EXIT APP
            else
                invalid();
        }
    }
}

//------------------------------------------------------------------------------
void Application::addCommands()
{
    // CRUD
    commands_["lstab"] = dynamo::ListTables::Ptr(new dynamo::ListTables());
    commands_["ctab"] = dynamo::CreateTable::Ptr(new dynamo::CreateTable());
    commands_["cctab"] = dynamo::CreateCompositeTable::Ptr(new dynamo::CreateCompositeTable());
    commands_["putitem"] = dynamo::PutItem::Ptr(new dynamo::PutItem());


    commands_["lsuser"] = cognito::ListUsers::Ptr(new cognito::ListUsers());
    commands_["getuser"] = cognito::GetUser::Ptr(new cognito::GetUser());
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

