#include "ubinos.h"
#include "config.h"

#ifndef SEM_WAITQ_H_

#define SEM_WAITQ_H_

int SEM_WQ_FULL(sem_pt sid);
int SEM_WQ_EMPTY(sem_pt sid);
//int Find_sem_Btask(int*, int, sem_pt);
int push_sem_task_into_WQ(unsigned char, unsigned char, sem_pt);
int get_sem_task_from_WQ(unsigned char*, unsigned char*, sem_pt);
int get_sem_task_from_WQ_position(unsigned char* tid, unsigned char* prio, sem_pt sid, int task_loc); //use for lock timed
int sem_prio_change(unsigned char tid, unsigned char chan_prio, sem_pt sid, int loc);

#endif