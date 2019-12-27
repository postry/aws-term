/*
 * createcompositetable.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/createcompositetable.hpp"
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/CreateTableRequest.h>
#include <aws/dynamodb/model/KeySchemaElement.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/ScalarAttributeType.h>
#include <iostream>

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
void CreateCompositeTable::execute(Args& args)
{
    const Aws::String region("ca-central-1");
    Aws::String table;
    args >> table;

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

    std::cout << "Creating table " << table
            << " with a composite primary key:\n"
                    "* Language - partition key\n"
                    "* Greeting - sort key\n";
    Aws::DynamoDB::Model::CreateTableRequest req;
    Aws::DynamoDB::Model::AttributeDefinition hashKey1, hashKey2;
    hashKey1.WithAttributeName("Language").WithAttributeType(
            Aws::DynamoDB::Model::ScalarAttributeType::S);
    req.AddAttributeDefinitions(hashKey1);
    hashKey2.WithAttributeName("Greeting").WithAttributeType(
            Aws::DynamoDB::Model::ScalarAttributeType::S);
    req.AddAttributeDefinitions(hashKey2);
    Aws::DynamoDB::Model::KeySchemaElement kse1, kse2;
    kse1.WithAttributeName("Language").WithKeyType(
            Aws::DynamoDB::Model::KeyType::HASH);
    req.AddKeySchema(kse1);
    kse2.WithAttributeName("Greeting").WithKeyType(
            Aws::DynamoDB::Model::KeyType::RANGE);
    req.AddKeySchema(kse2);
    Aws::DynamoDB::Model::ProvisionedThroughput thruput;
    thruput.WithReadCapacityUnits(5).WithWriteCapacityUnits(5);
    req.SetProvisionedThroughput(thruput);
    req.SetTableName(table);
    const Aws::DynamoDB::Model::CreateTableOutcome &result =
            dynamoClient.CreateTable(req);
    if (result.IsSuccess())
    {
        std::cout << "Table \""
                << result.GetResult().GetTableDescription().GetTableName()
                << "\" was created!\n";
    }
    else
    {
        std::cout << "Failed to create table:"
                << result.GetError().GetMessage();
    }
};
} /* dynamo namespace */

} /* app namespace */
