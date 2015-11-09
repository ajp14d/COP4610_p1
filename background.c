#include "background.h"

extern struct ProcessEntry* process_queue[];

void InitBackgroundProcessing()
{
	int i;
	for (i = 0; i < PQUEUE_SIZE; i++)
	{
		process_queue[i] = NULL;
	}
}

void QueueProcess(struct ProcessEntry* p)
{
	int i;
	// find first available slot
	for (i = 0; i < PQUEUE_SIZE; i++)
	{
		if (process_queue[i] == NULL)
		{
			process_queue[i] = p;
			PrintProcessEntryStart(process_queue[i], i);
			break;
		}
	}
}

void CheckProcessQueue()
{
	int i;
	for (i = 0; i < PQUEUE_SIZE; i++)
	{
		if (process_queue[i] != NULL)
		{
			if (CheckProcess(process_queue[i]))
			{
				RemoveProcess(i);
			}
		}
	}
}

void OnExitProcessQueueWait()
{
	int processes_running = 1;
	while(processes_running)
	{
		CheckProcessQueue();
		int i = 0;
		for (i = 0; i < PQUEUE_SIZE; i++)
		{
			if (process_queue[i] != NULL)
			{
				processes_running = 1;
				break;
			}
		}
		if (i == PQUEUE_SIZE)
		{
			processes_running = 0;
		}
	}
}

void RemoveProcess(int index)
{
	if (index >= 0 && index < PQUEUE_SIZE)
	{
		if (process_queue[index] != NULL)
		{
			PrintProcessEntryComplete(process_queue[index], index);
			FreeProcessEntry(process_queue[index]);
			process_queue[index] = NULL;
		}
	}
}

struct ProcessEntry* CreateProcessEntry(int pid_1, int pid_2, char* cmd)
{
	struct ProcessEntry* ret = (struct ProcessEntry*)calloc(1, sizeof(struct ProcessEntry));
	ret->pid_1 = pid_1;
	ret->pid_2 = pid_2;
	ret->cmd = (char*)calloc(strlen(cmd)+1,sizeof(char));
	strcpy(ret->cmd, cmd);
	return ret;
}

void FreeProcessEntry(struct ProcessEntry* p)
{
	free(p->cmd);
	free(p);
}

int CheckProcess(struct ProcessEntry* p)
{
	int status;
	int waitpid_ret;
	if (p->pid_2 != -1)
	{
		waitpid_ret = waitpid(p->pid_2, &status, WNOHANG);
		if (waitpid_ret == 0)
		{
			return 0;
		}
		else if (waitpid_ret == -1)
		{
			printf("Error in child process: %s\n", p->cmd);
		}

	}
	waitpid_ret = waitpid(p->pid_1, &status, WNOHANG);
	if (waitpid_ret == 0)
	{
		return 0;
	}
	else if (waitpid_ret == -1)
	{
		printf("Error in child process: %s\n", p->cmd);
	}
	else
	{
		return 1;
	}
	return 1;	// fix compiler warning
}

void PrintProcessEntryStart(const struct ProcessEntry* p, int pos)
{
	if (p != NULL)
	{
		if (p->pid_2 != -1)
		{
			printf("[%i]\t[%i][%i]\n", pos, p->pid_1, p->pid_2);
		}
		else
		{
			printf("[%i]\t[%i]\n", pos, p->pid_1);
		}
	}
}

void PrintProcessEntryComplete(const struct ProcessEntry* p, int pos)
{
	if (p != NULL)
	{
		printf("[%i]+\t[%s]\n", pos, p->cmd);
	}
}
