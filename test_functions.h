// A series of test functions for each function written for the project
#ifndef _TEST_FUNCTIONS_H
#define _TEST_FUNCTIONS_H

#include "background.h"
#include "pipe.h"

void TestDeleteCharacter();
void TestParseWhitespace(const char* test_line);
void TestDynStrCat();
void TestRemoveLastDir();
void TestIsCommand();
void TestDynStrPushBack();
void TestExpandVariables();
void TestReplaceSubStr();
void TestBuildPath();
void TestPathEnvBuildPath();
void TestArrayOps();
void TestVecContainsStr();
void TestProcessQueue();
void TestArgvToString();
void TestOnePipe();

#endif
