/*
 * createtable.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/createtable.hpp"
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
void CreateTable::execute(Args& args)
{
    const Aws::String region("ca-central-1");
    Aws::String table;
    args >> table;

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

    std::cout << "Creating table " << table
            << " with a simple primary key: \"Name\"" << std::endl;

    Aws::DynamoDB::Model::CreateTableRequest req;
    Aws::DynamoDB::Model::AttributeDefinition haskKey;
    haskKey.SetAttributeName("Name");
    haskKey.SetAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
    req.AddAttributeDefinitions(haskKey);
    Aws::DynamoDB::Model::KeySchemaElement keyscelt;
    keyscelt.WithAttributeName("Name").WithKeyType(
            Aws::DynamoDB::Model::KeyType::HASH);
    req.AddKeySchema(keyscelt);
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
                << " created!" << std::endl;
    }
    else
    {
        std::cout << "Failed to create table: "
                << result.GetError().GetMessage();
    }
};

} /* namespace dynamo */

} /* namespace app */
