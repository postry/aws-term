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
    // DYNAMO DB
    addCommand<dynamo::ListTables>("lstab");
    addCommand<dynamo::CreateTable>("ctab");
    addCommand<dynamo::CreateCompositeTable>("cctab");
    addCommand<dynamo::PutItem>("putitem");
    addCommand<dynamo::GetItem>("getitem");
    addCommand<dynamo::DeleteItem>("delitem");
    addCommand<dynamo::UpdateItem>("upditem");

    // USERS
    addCommand<cognito::ListUsers>("lsuser");
    addCommand<cognito::GetUser>("getuser");

    //IOT
    addCommand<iot::ListThings>("lsthings");
    addCommand<iot::GetThing>("getthing");
    addCommand<iot::UpdateThing>("updatething");
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

