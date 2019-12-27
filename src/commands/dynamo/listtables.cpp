/*
 * listtables.cpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#include "commands/dynamo/listtables.hpp"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/DescribeTableRequest.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/GetItemResult.h>
#include <aws/dynamodb/model/ScanRequest.h>
#include <aws/dynamodb/model/ScanResult.h>

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
void ListTables::execute(Args& args)
{

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "ca-central-1";
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

    Aws::DynamoDB::Model::ListTablesRequest ltr;
    ltr.SetLimit(50);
    do
    {
        const Aws::DynamoDB::Model::ListTablesOutcome& lto = dynamoClient.ListTables(ltr);
        if (!lto.IsSuccess())
        {
            std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
            return;
        }
        for (const auto& s : lto.GetResult().GetTableNames())
        {
            std::cout << s << std::endl;
            {
                Aws::DynamoDB::Model::DescribeTableRequest dtr;
                dtr.SetTableName(s);

                const Aws::DynamoDB::Model::DescribeTableOutcome& result = dynamoClient.DescribeTable(dtr);

                if (result.IsSuccess())
                {
                    const Aws::DynamoDB::Model::TableDescription& td = result.GetResult().GetTable();
                    std::cout << "Table name  : " << td.GetTableName() << std::endl;
                    std::cout << "Table ARN   : " << td.GetTableArn() << std::endl;
                    std::cout << "Status      : " << Aws::DynamoDB::Model::TableStatusMapper::GetNameForTableStatus(td.GetTableStatus()) << std::endl;
                    std::cout << "Item count  : " << td.GetItemCount() << std::endl;
                    std::cout << "Size (bytes): " << td.GetTableSizeBytes() << std::endl;

                    const Aws::DynamoDB::Model::ProvisionedThroughputDescription& ptd = td.GetProvisionedThroughput();
                    std::cout << "Throughput" << std::endl;
                    std::cout << "  Read Capacity : " << ptd.GetReadCapacityUnits() << std::endl;
                    std::cout << "  Write Capacity: " << ptd.GetWriteCapacityUnits() << std::endl;

                    const Aws::Vector<Aws::DynamoDB::Model::AttributeDefinition>& ad = td.GetAttributeDefinitions();
                    std::cout << "Attributes" << std::endl;
                    for (const auto& a : ad)
                        std::cout << "  " << a.GetAttributeName() << " (" <<
                        Aws::DynamoDB::Model::ScalarAttributeTypeMapper::GetNameForScalarAttributeType(a.GetAttributeType()) <<
                        ")" << std::endl;

                    Aws::DynamoDB::Model::ScanRequest scanRequest;
                    std::cout << "Scanning " << s << std::endl;
                    scanRequest.WithTableName(s);

                    Aws::DynamoDB::Model::ScanOutcome scanOutcome = dynamoClient.Scan(scanRequest);
                    if (scanOutcome.IsSuccess())
                        for (auto& map :  scanOutcome.GetResult().GetItems())
                        {
                            std::cout << " >>><<<" << s << std::endl;
                            for (auto& kv : map)
                                std::cout << "  " << kv.first << " : " << kv.second.GetS() <<std::endl;
                        }
                }
                else
                {
                    std::cout << "Failed to describe table: " << result.GetError().GetMessage();
                }
            }
        }
        ltr.SetExclusiveStartTableName(lto.GetResult().GetLastEvaluatedTableName());
    } while (!ltr.GetExclusiveStartTableName().empty());
}

} /* namespace dynamo */

} /* namespace app */
