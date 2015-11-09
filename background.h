#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include<stdlib.h>	// for NULL decleration
#include<string.h>	// for string functionality (strcpy)
#include<stdio.h>	// for printing out processes
#include<sys/wait.h>

struct ProcessEntry
{
	// pid for first command
	int pid_1;
	// if there is redirection, this contains
	// the pid for the second command
	// if not, this assumes the value -1
	int pid_2;
	// the cmd used to spawn the process
	char* cmd;
};

// global process queue
#define PQUEUE_SIZE 256
struct ProcessEntry* process_queue[PQUEUE_SIZE];

void InitBackgroundProcessing();

void QueueProcess(struct ProcessEntry* p);

void CheckProcessQueue();

void OnExitProcessQueueWait();

void RemoveProcess(int index);

struct ProcessEntry* CreateProcessEntry(int pid_1, int pid_2,
	char* cmd);

void FreeProcessEntry(struct ProcessEntry* p);

int CheckProcess(struct ProcessEntry* p);

void PrintProcessEntryStart(const struct ProcessEntry* p, int pos);

void PrintProcessEntryComplete(const struct ProcessEntry* p, int pos);

#endif
