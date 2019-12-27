/*
 * listusers.cpp
 *
 *  Created on: Dec. 26, 2019
 *      Author: elagon
 */

#include "commands/cognito/listusers.hpp"

#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include "aws/cognito-idp/CognitoIdentityProviderClient.h"
#include "aws/cognito-idp/model/ListUsersRequest.h"
#include "aws/cognito-idp/model/ListUsersResult.h"

namespace app
{
namespace cognito
{

//------------------------------------------------------------------------------
void  ListUsers::execute(Args& args)
{
    Aws::String regionId = "ca-central-1";
    Aws::String clientId = "3q8qcfgn20f5rtlpcttflkes2v";
    Aws::String username = "testuser6";
    Aws::String password = "temppwd";
    Aws::String userPoolId = "NlutBZjBt";       // without region
    Aws::String identityPoolId = "a83d3fd5-ffb4-41a6-830a-2666d26fdcd2";// without region

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = regionId;

    Aws::CognitoIdentityProvider::Model::ListUsersRequest request;
    request.SetUserPoolId(regionId + "_" + userPoolId);

    Aws::CognitoIdentityProvider::CognitoIdentityProviderClient client(clientConfig);
    Aws::CognitoIdentityProvider::Model::ListUsersOutcome outcome = client.ListUsers(request);

    if (outcome.IsSuccess())
    {
        Aws::CognitoIdentityProvider::Model::ListUsersResult& response = outcome.GetResult();
        for (const auto& user : response.GetUsers())
            std::cout << user.GetUsername() << std::endl;
    }
    else
    {
        std::cerr << outcome.GetError() << std::endl;
    }
};

} /* namespace cognito */

} /* namespace app */
