#include "xiso/common/configure/properties.h"
#include "gtest_envir.h"
#include <gtest/gtest.h>

TEST(TEST_CONFIGURE, CONFIGURE)
{
    std::string filepath = GTestEnvir::src_dir + "/config.ini";

    // 写配置
    xiso::common::configure::PropertyTree writePropertyTree;
    writePropertyTree.set("server", "ip", "192.168.1.100");
    writePropertyTree.set("server", "port", 10086);
    writePropertyTree.set("database", "ip", "127.0.0.1");
    writePropertyTree.set("database", "port", 3306);
    writePropertyTree.set("database", "username", "root");
    writePropertyTree.set("database", "password", "12345678");
    xiso::common::configure::write_profile(filepath, writePropertyTree);

    // 读配置
    xiso::common::configure::PropertyTree readPropertyTree;
    xiso::common::configure::read_profile(filepath, readPropertyTree);
    std::string serverIp     = readPropertyTree.get("server", "ip").asString();
    uint16_t    serverPort   = readPropertyTree.get("server", "port").asUInt();
    std::string databaseIp   = readPropertyTree.get("database", "ip").asString();
    uint16_t    databasePort = readPropertyTree.get("database", "port").asUInt();
    std::string databaseUser = readPropertyTree.get("database", "username").asString();
    std::string databasePwd  = readPropertyTree.get("database", "password").asString();

    // 清理数据
    remove(filepath.c_str());

    // 验证配置
    EXPECT_STREQ(serverIp.c_str(), "192.168.1.100");
    EXPECT_EQ(serverPort, 10086);
    EXPECT_STREQ(databaseIp.c_str(), "127.0.0.1");
    EXPECT_EQ(databasePort, 3306);
    EXPECT_STREQ(databaseUser.c_str(), "root");
    EXPECT_STREQ(databasePwd.c_str(), "12345678");
}