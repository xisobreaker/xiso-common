#include "gtest_envir.h"
#include <gtest/gtest.h>

std::string GTestEnvir::src_dir = "";
std::string GTestEnvir::tmp_dir = "";

void GTestEnvir::SetUp()
{
    src_dir = testing::SrcDir();
    tmp_dir = testing::TempDir();
}

void GTestEnvir::TearDown()
{
}