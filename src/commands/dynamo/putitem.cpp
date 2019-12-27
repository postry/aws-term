/*
 * putitem.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/putitem.hpp"

#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/PutItemResult.h>
#include <iostream>

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
void PutItem::execute(Args& args)
{
    const Aws::String region("ca-central-1");
    Aws::String table;
    args >> table;

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName(table);
    while (args)
    {
        Aws::String arg;
        args >> arg;
        std::cout << "arg: '" << arg << "'"<<std::endl;
        if (not arg.empty())
        {
            const Aws::Vector<Aws::String> &flds =
                    Aws::Utils::StringUtils::Split(arg, '=');
            if (flds.size() == 2)
            {
                Aws::DynamoDB::Model::AttributeValue val;
                val.SetS(flds[1]);
                pir.AddItem(flds[0], val);
            }
            else
            {
                std::cout << "Invalid argument: " << arg << std::endl;
            }
        }
    }

    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        std::cout << result.GetError().GetMessage() << std::endl;
    }
};

} /* dynamo namespace */

} /* app namespace */
