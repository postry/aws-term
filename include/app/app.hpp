/*
 * app.hpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <map>
#include <memory>
#include <string>
#include "commands/command.hpp"

namespace app
{

class Application
{
public:
    using Ptr = std::unique_ptr<Application>;

    static Ptr create();

    void run();

    void addCommands();

private:
    Application() = default;
    void ready();
    void invalid();
    std::map<std::string, Command::Ptr> commands_;
};

} // app namespace



#endif /* APP_HPP_ */
