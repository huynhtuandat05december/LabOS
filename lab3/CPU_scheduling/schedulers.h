#include <stdio.h>
#include "process.h"

void print(Process p[], int n)
{
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_response_time = 0;
	for (int i = 0; i < n; i++)
	{
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}
	printf("\tAverage Waiting Time   : %-2.2lf\n", 1.0 * total_waiting_time / n);
	printf("\tAverage Turnaround Time: %-2.2lf\n", 1.0 * total_turnaround_time / n);
	printf("\tAverage Response Time  : %-2.2lf\n\n", 1.0 * total_response_time / n);

	printf("\t| PID | Arrive Time | Burst Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |\n");
	for (int i = 0; i < n; i++)
	{
		printf("\t| %3s |     %3d     |     %3d    |    %3d   |     %3d     |      %3d        |      %3d     |        %3d      |\n",
			   p[i].id, p[i].arrive_time, p[i].burst, p[i].priority, p[i].return_time, p[i].response_time, p[i].waiting_time, p[i].turnaround_time);
	}
	printf("\n");
}

void FCFS(Process *p, int num_process)
{
	int now = 0, counter = 0;

	while (counter < num_process)
	{
		if (now >= p[counter].arrive_time)
		{
			if (p[counter].executing == false && p[counter].tmp_burst_ > 0)
			{
				// first time executing
				p[counter].response_time = now - p[counter].arrive_time;
				p[counter].waiting_time = now - p[counter].arrive_time;
				p[counter].executing = true;
			}
			else if (p[counter].tmp_burst_ == 0)
			{
				p[counter].return_time = now;
				p[counter].turnaround_time = now - p[counter].arrive_time;
				p[counter].completed = true;
				p[counter].executing = false;

				counter += 1;
				// if finish => change to the next process
				// do not update now before updating p[counter+1].response_time ....
				continue;
			}
			p[counter].tmp_burst_ -= 1;
		}
		now += 1;
	}
}

void SJF(Process *p, int num_process)
{
	int now = 0, counter = 0;
	int smallest = 9999;
	int temp = -1;
	while (counter < num_process)
	{
		for (int i = 0; i < num_process; i++)
		{
			if (p[i].arrive_time <= now && p[i].completed == false)
			{
				if (p[i].burst < smallest)
				{
					smallest = p[i].burst;
					temp = i;
				}
			}
		}
		if (temp != -1)
		{
			p[temp].response_time = now - p[temp].arrive_time;
			p[temp].waiting_time = now - p[temp].arrive_time;
			now += p[temp].burst;
			p[temp].return_time = now;
			p[temp].turnaround_time = now - p[temp].arrive_time;
			p[temp].completed = true;
			counter++;
			smallest = 9999;
			temp = -1;
		}
		else
		{
			now++;
		}
	}
}

void Priority_Scheduling(Process *p, int num_process)
{
	int now = 0, counter = 0;
	int biggest = -1;
	int temp = -1;
	while (counter < num_process)
	{
		for (int i = 0; i < num_process; i++)
		{
			if (p[i].arrive_time <= now && p[i].completed == false)
			{
				if (p[i].priority > biggest)
				{
					biggest = p[i].priority;
					temp = i;
				}
			}
		}
		if (temp != -1)
		{
			if (p[temp].completed == false && p[temp].executing == false)
			{
				p[temp].response_time = now - p[temp].arrive_time;
				p[temp].executing = true;
			}
			p[temp].tmp_burst_--;
			now++;
			if (p[temp].tmp_burst_ == 0)
			{
				p[temp].completed = true;
				p[temp].return_time = now;
				p[temp].turnaround_time = now - p[temp].arrive_time;
				p[temp].waiting_time = now - p[temp].arrive_time - p[temp].burst;
				counter++;
			}
			biggest = -1;
			temp = -1;
		}
		else
		{
			now++;
		}
	}
}

void RR(Process *p, int num_process, Quantum q)
{
	int now = 0, counter = 0;
	int temp = -1;
	int check = -1;
	temp = 0;
	check = 0;
	now = p[0].arrive_time;
	while (counter < num_process)
	{
		if (p[temp].completed == false && p[temp].executing == false)
		{
			p[temp].response_time = now - p[temp].arrive_time;
			p[temp].executing = true;
		}
		if (p[temp].completed == false)
		{
			if (p[temp].tmp_burst_ > q)
			{
				p[temp].tmp_burst_ -= q;
				now += q;
			}
			else
			{
				p[temp].completed = true;
				p[temp].tmp_burst_ -= q;
				now = now + q + p[temp].tmp_burst_;
				p[temp].return_time = now;
				p[temp].turnaround_time = p[temp].return_time - p[temp].arrive_time;
				p[temp].waiting_time = p[temp].return_time - p[temp].arrive_time - p[temp].burst;
				counter++;
			}
		}
		do
		{
			if (check == num_process - 1)
			{
				check = 0;
			}
			else
			{
				check++;
			}
			if (check == temp)
			{
				if (p[check].completed == false)
				{
					break;
				}
				else
				{
					now++;
					break;
				}
			}
			else
			{
				if (p[check].arrive_time <= now && p[check].completed == false)
				{
					break;
				}
			}
		} while (true);
		temp = check;
	}
}
