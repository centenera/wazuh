#include "gtest/gtest.h"
#include <kvdb/kvdb.hpp>


TEST(kvdbTests, column_family_creation_deletion)
{
    bool ret = CreateKVDB();
    ASSERT_TRUE(ret);
    ret = CreateColumnFamily("IP_BLACKLIST");
    ASSERT_TRUE(ret);
    ret = DeleteColumnFamily("IP_BLACKLIST");
    ASSERT_TRUE(ret);
    ret = CreateColumnFamily("");
    ASSERT_TRUE(!ret);
    ret = DeleteColumnFamily("NOT_AVAILABLE");
    ASSERT_TRUE(!ret);
    ret = DestroyKVDB();
    ASSERT_TRUE(ret);
}

TEST(kvdbTests, read_write_column_family)
{
    bool ret = CreateKVDB();
    ASSERT_TRUE(ret);
    ret = CreateColumnFamily("IP_BLACKLIST");
    ASSERT_TRUE(ret);
    ret = WriteToColumnFamily("IP_BLACKLIST", "someKey", "192.168.10.2");
    ASSERT_TRUE(ret);
    ret = WriteToColumnFamily("IP_BLACKLIST", "someKey", "127.0.0.1");
    ASSERT_TRUE(ret);
    std::string val;
    ret = ReadToColumnFamily("IP_BLACKLIST", "someKey", val);
    ASSERT_TRUE(ret);
    ASSERT_EQ(val,"127.0.0.1");
    ret = DeleteKeyInColumnFamily("IP_BLACKLIST", "someKey");
    ASSERT_TRUE(ret);
    ret = ReadToColumnFamily("IP_BLACKLIST", "someKey", val);
    ASSERT_TRUE(!ret);
    ret = DeleteColumnFamily("IP_BLACKLIST");
    ASSERT_TRUE(ret);
    ret = DestroyKVDB();
    ASSERT_TRUE(ret);
}