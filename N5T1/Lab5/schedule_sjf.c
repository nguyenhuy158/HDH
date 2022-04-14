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
    // yc 1.2
    for (int h = 0; h < i - 1; h++)
    {
        for (int k = 0; k < i - h - 1; k++)
        {
            if (task[k].burst > task[k + 1].burst)
            {
                Task temp = task[k + 1];
                task[k + 1] = task[k];
                task[k] = temp;
            }
        }
    }

    int j = 0;
    int time = 0;
    float arround = 0;
    float aver1;

    // yc 1.1
    float wait = 0;
    float aver2;
    for (j = 0; j < i; j++)
    {
        run(&task[j], time, task[j].burst);
        time += task[j].burst;

        arround += time - task[j].arrival;
        wait += time - task[j].burst;
    }
    aver1 = arround / 8;
    aver2 = wait / 8;
    printf("Thoi gian xoay vong trung binh cua cac tien trinh la: %.2f \n", aver1);
    printf("Thoi gian cho trung binh cua cac tien trinh la: %.2f \n", aver2);
}
