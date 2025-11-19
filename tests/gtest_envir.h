#pragma once

#include <gtest/gtest.h>

class GTestEnvir : public testing::Environment
{
public:
    void SetUp() override;
    void TearDown() override;

public:
    static std::string src_dir;
    static std::string tmp_dir;
};