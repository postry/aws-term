/*
 * getuser.cpp
 *
 *  Created on: Dec. 26, 2019
 *      Author: elagon
 */

#include "commands/cognito/getuser.hpp"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include "aws/cognito-idp/CognitoIdentityProviderClient.h"
#include "aws/cognito-idp/model/GetUserRequest.h"
#include "aws/cognito-idp/model/GetUserResult.h"
#include "aws/cognito-idp/model/InitiateAuthRequest.h"
#include "aws/cognito-idp/model/InitiateAuthResult.h"

namespace app
{

namespace cognito
{

//------------------------------------------------------------------------------
void GetUser::execute(Args& args)
{
    Aws::String regionId = "ca-central-1";
    Aws::String clientId = "3q8qcfgn20f5rtlpcttflkes2v";
    Aws::String username = "testuser6";
    Aws::String password = "temppwd";
    Aws::String userPoolId = "NlutBZjBt";       // without region
    Aws::String identityPoolId = "a83d3fd5-ffb4-41a6-830a-2666d26fdcd2";// without region

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = regionId;

    Aws::Map<Aws::String, Aws::String> authParameters;
    authParameters["USERNAME"] = username;
    authParameters["PASSWORD"] = password;

    Aws::CognitoIdentityProvider::CognitoIdentityProviderClient cipClient(
            clientConfig);

    Aws::CognitoIdentityProvider::Model::InitiateAuthRequest authRequest;
    authRequest.SetClientId(clientId);
    authRequest.SetAuthFlow(Aws::CognitoIdentityProvider::Model::AuthFlowType::USER_PASSWORD_AUTH);
    authRequest.SetAuthParameters(authParameters);

    Aws::CognitoIdentityProvider::Model::InitiateAuthOutcome authOutcome = cipClient.InitiateAuth(authRequest);

    if (authOutcome.IsSuccess())
    {
        Aws::CognitoIdentityProvider::Model::InitiateAuthResult authResult = authOutcome.GetResult();
        std::cout << authResult.GetAuthenticationResult().GetAccessToken() << std::endl;

        Aws::CognitoIdentityProvider::Model::GetUserRequest request;
        request.SetAccessToken(authResult.GetAuthenticationResult().GetAccessToken());
        Aws::CognitoIdentityProvider::Model::GetUserOutcome outcome = cipClient.GetUser(request);

        if (outcome.IsSuccess())
        {
            Aws::CognitoIdentityProvider::Model::GetUserResult& response = outcome.GetResult();
            for (const auto& att : response.GetUserAttributes())
                std::cout << att.GetName() << " : "<< att.GetValue() << std::endl;
        }
        else
        {
            std::cerr << outcome.GetError() << std::endl;
        }
    }
    else
    {
        std::cerr << authOutcome.GetError() << std::endl;
    }
}

} /* namespace cognito */

} /* namespace app */
