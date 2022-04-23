#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "cpu.h"
#include "schedulers.h"

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#define SIZE 100

static int i = 0;
Task task[SIZE];
void add(char *name, int priority, int arrival, int burst)
{
    task[i].name = name;
    task[i].priority = priority;
    task[i].arrival = arrival;
    task[i].burst = burst;
    i++;
}

void schedule()
{
    int j = 0;
    int time = 0;
    int timeQuantum = 10;

    while (i >= 0)
    {
        if (task[j].burst <= timeQuantum)
        {
            run(&task[j], time, task[j].burst);
            time += task[j].burst;
            for (int h = 0; h < i - 1; h++)
            {
                task[h] = task[h + 1];
            }
            i--;
        }
        else
        {
            run(&task[j], time, timeQuantum);
            time += timeQuantum;
            task[j].burst -= timeQuantum;
        }
    }
}
