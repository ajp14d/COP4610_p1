#include "test_functions.h"
#include "utility.h"
#include "parse.h"
#include<stdio.h>
#include<string.h>

void TestDeleteCharacter()
{
	printf("TestDeleteCharacter()\n");
	char* test_line = "This is a test line!\n";
	char* line = (char*)calloc(strlen(test_line)+1, sizeof(char));
	
	strcpy(line, test_line);
	printf("Deleting the word test from: ");
	printf(line);
	printf("\n");
	printf("The line length is: %i\n", (int)strlen(line));
	
	line = DeleteCharacter(line, 10, 13);
	printf("The transformed line is: ");
	printf(line);
	printf("\n");
	printf("The line length is: %i", (int)strlen(line));
	printf("\n\n\n");
	free(line);
}

void TestParseWhitespace(const char* test_line)
{
	//char* test_line = "    TEST!   HELLO! 	Again, test! test 	\ntest";
	printf("TestParseWhitespace()\n");
	char* line = (char*)calloc(strlen(test_line)+1, sizeof(char));

	strcpy(line, test_line);
	printf("Parsing whitespace from: ");
	printf(line);
	printf("\n");
	
	line = ParseWhitespace(line);
	printf("Line after parsing whitespace: ");
	printf(line);
	printf("\n\n\n");
	free(line);
}

void TestDynStrCat()
{
	const char* str1 = "Hello ";
	const char* str2 = "World!\n";

	char* str3 = (char*)calloc(7, sizeof(char));
	char* str4 = (char*)calloc(8, sizeof(char));

	strcpy(str3, str1);
	strcpy(str4, str2);

	str3 = DynStrCat(str3, str4);

	printf(str3);
	printf("%i\n", (int)strlen(str3));
	free(str3);
	free(str4);
}

void TestRemoveLastDir()
{
	const char* str = "/home/me/test_dir/";
	char* path = (char*)calloc(strlen(str)+1,sizeof(char));

	strcpy(path, str);
	printf("Path before: %s\n", path);

	path = RemoveLastDir(path);

	printf("Path after: %s\n", path);

	free(path);

	const char* str2 = "/home/me/test_dir";
	path = (char*)calloc(strlen(str2)+1, sizeof(char));
	strcpy(path, str2);
	printf("Path before: %s\n", path);
	path = RemoveLastDir(path);
	printf("Path after: %s\n", path);
	free(path);

	const char* str3 = "/";
	path = (char*)calloc(strlen(str3)+1, sizeof(char));
	strcpy(path, str3);
	printf("Path before: %s\n", path);
	path = RemoveLastDir(path);
	printf("Path after: %s\n", path);
	free(path);
}

void TestIsCommand()
{

	char* args[] = {"ls", "cd", "test.x", "not_a_program", "etime", NULL};

	size_t it = 0;
	char* tmp = args[it];
	while (tmp != NULL)
	{
		fflush(stdout);
		printf("%s %i\n", tmp, IsCommand(args, it));
		IsCommand(args,it);
		tmp = args[++it];
	}

}

void TestDynStrPushBack()
{
	char test[] = "String";
	char* str = (char*)calloc(strlen(test)+1, sizeof(char));
	strcpy(str, test);
	printf("Before: %s\n", str);
	str = DynStrPushBack(str, '.');
	printf("After: %s\n", str);
}

void TestExpandVariables()
{
	char test[] = "$PWD/THIS_TEST/$DEBUG_ENV/AGAIN_TEST/$DEBUG_ENV $PWD $HOME/t $HOME $PWD $$$ $P/TEST/test/";
	char** args = ParseArguments(test);
	printf("BEFORE: \n");
	PrintArgVector(args);
	args = ExpandVariables(args);
	printf("AFTER: \n");
	PrintArgVector(args);
}

void TestReplaceSubStr()
{
	char* str1 = "I am testing";
	size_t start = 5;
	size_t end = 11;
	char* str2 = "going crazy";

	char* dyn_str1 = (char*)calloc(strlen(str1)+1, sizeof(char));
	strcpy(dyn_str1, str1);

	printf("Before: %s\n", dyn_str1);
	dyn_str1 = ReplaceSubStr(dyn_str1, start, end, str2);
	printf("After: %s\n", dyn_str1);

	char* str3 = "He is definitely";
	printf("Before: %s\n", dyn_str1);
	dyn_str1 = ReplaceSubStr(dyn_str1, 0, 3, str3);
	printf("After: %s\n", dyn_str1);

	char* str4 = "maybe";
	printf("Before: %s\n", dyn_str1);
	dyn_str1 = ReplaceSubStr(dyn_str1, 6, 15, str4);
	printf("After: %s\n", dyn_str1);

	free(dyn_str1);

}

void TestBuildPath()
{
	char str[] = "~/COP4610";
	char* dyn_str = (char*)calloc(strlen(str)+1,sizeof(char));
	strcpy(dyn_str, str);
	printf("Before: %s\n", dyn_str);
	dyn_str = BuildPath(dyn_str);
	printf("After: %s\n", dyn_str);
	
	char str2[] = "./COP4610";
	char* dyn_str2 = (char*)calloc(strlen(str2)+1,sizeof(char));
	strcpy(dyn_str2, str2);
	printf("Before: %s\n", dyn_str2);
	dyn_str2 = BuildPath(dyn_str2);
	printf("After: %s\n", dyn_str2);

	char str3[] = "../COP4610";
	char* dyn_str3 = (char*)calloc(strlen(str3)+1,sizeof(char));
	strcpy(dyn_str3, str3);
	printf("Before: %s\n", dyn_str3);
	dyn_str3 = BuildPath(dyn_str3);
	printf("After: %s\n", dyn_str3);

	char str4[] = "~/COP4610/./Projects/..";
	char* dyn_str4 = (char*)calloc(strlen(str4)+1,sizeof(char));
	strcpy(dyn_str4, str4);
	printf("Before: %s\n", dyn_str4);
	dyn_str4 = BuildPath(dyn_str4);
	printf("After: %s\n", dyn_str4);

	char str5[] = "~/COP4610/./Projects/../../COP4610/./..";
	char* dyn_str5 = (char*)calloc(strlen(str5)+1,sizeof(char));
	strcpy(dyn_str5, str5);
	printf("Before: %s\n", dyn_str5);
	dyn_str5 = BuildPath(dyn_str5);
	printf("After: %s\n", dyn_str5);

	free(dyn_str);
	free(dyn_str2);
	free(dyn_str3);
	free(dyn_str4);
	free(dyn_str5);
}

void TestPathEnvBuildPath()
{
	char str[] = "ls";
	char* dyn_str = (char*)calloc(strlen(str)+1,sizeof(char));
	strcpy(dyn_str, str);
	printf("Before: %s\n", dyn_str);
	dyn_str = PathEnvBuildPath(dyn_str);
	printf("After: %s\n", dyn_str);

	char str2[] = "test.x";
	char* dyn_str2 = (char*)calloc(strlen(str2)+1,sizeof(char));
	strcpy(dyn_str2, str2);
	printf("Before: %s\n", dyn_str2);
	dyn_str2 = PathEnvBuildPath(dyn_str2);
	printf("After: %s\n", dyn_str2);

	free(dyn_str);
	free(dyn_str2);
}

void TestArrayOps()
{
	char* str = ReadInput();
	char** argv = ParseInput(str);
	char str_push[] = "INSERTED";
	char* dyn_str_push = (char*)calloc(strlen(str_push)+1,sizeof(char));
	strcpy(dyn_str_push, str_push);

	printf("Before: \n");
	PrintArgVector(argv);
	argv = ArrayPushBack(argv, dyn_str_push);
	printf("Push back: \n");
	PrintArgVector(argv);
	argv = ArrayRemoveElement(argv, 0);
	printf("Removed front: \n");
	PrintArgVector(argv);

	BigFree(argv);
	free(dyn_str_push);
}

void TestVecContainsStr()
{
	char* str = ReadInput();
	char** argv = ParseInput(str);
	char sequence[] = "<";

	PrintArgVector(argv);
	printf("%i\n", VecContainsStr(argv, sequence));
}

void TestProcessQueue()
{
	InitBackgroundProcessing();
	struct ProcessEntry* p1 = CreateProcessEntry(1000, 2000, "ls -al | more");
	struct ProcessEntry* p2 = CreateProcessEntry(101, -1, "cd /");
	QueueProcess(p1);
	QueueProcess(p2);
	CheckProcessQueue();
}

void TestArgvToString()
{
	char* str = ReadInput();
	char** argv = ParseInput(str);
	PrintArgVector(argv);
	char* str2 = ArgvToString(argv);

	printf("%s\n", str2);
	free(str2);
	BigFree(argv);
}

void TestOnePipe()
{
	char* argv1[] = {"/bin/cat", "shell.c", NULL};
	char* argv2[] = {"/bin/more", NULL};
	int background = 0;
	char cmd[] = "Doesn't matter yet\n";
	OnePipe(argv1, argv2, background, cmd);
	
	char* argv3[] = {"/bin/ls", NULL};
	char* argv4[] = {"/bin/more", NULL};
	char* argv5[] = {"/bin/grep", "she", NULL};
	TwoPipe(argv3, argv4, argv5, background, cmd);
	
	char* argv6[] = {"/bin/ls", "-U", "-l", NULL};
	char* argv7[] = {"/bin/sort", NULL};
	char* argv8[] = {"/bin/more", NULL};
	char* argv9[] = {"/bin/grep", "c", NULL};
	ThreePipe(argv6, argv7, argv8, argv9, background, cmd);
}
