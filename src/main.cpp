/*
 * main.cpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#include <iostream>
#include <aws/core/Aws.h>
#include "app/app.hpp"

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    try
    {
        app::Application::Ptr app = app::Application::create();
        app->addCommands();
        app->run();
    }
    catch (const std::exception &x)
    {
        std::cerr << x.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Fatal error" << std::endl;
    }

    Aws::ShutdownAPI(options);
    return 0;
}
