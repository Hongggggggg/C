#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"
#include "task.h"
#include <unistd.h>

typedef struct person
{
    int age;
    char name[10];
} person_t;

typedef struct teacher
{
    person_t common;
    ListObj list;
    char class[10];
}teacher_t;

typedef struct student
{
    person_t common;
    ListObj list;
    char major[10];
    int score;
}student_t;

TimesilceTaskObj task_1, task_2, task_3, task_4, task_5;

void* timeslice_exec_thread(void *arg)
{
    printf("timeslice_exec_thread\r\n");
    while (1)
    {
        timeslice_exec();
    }
}

void* timeslce_exec_thread(void *arg)
{
    while(1)
    {
        timeslice_tick();
        usleep(100000);
    }
}

void task1_hdl(void)
{
    printf(">> task 1 is running ...\n");
}

void task2_hdl(void)
{
    printf(">> task 2 is running ...\n");
}

void task3_hdl(void)
{
    printf(">> task 3 is running ...\n");
}

void task4_hdl(void)
{
    printf(">> task 4 is running ...\n");
}

void task5_hdl(void)
{
    printf(">> task 5 is running ...\n");
}


void task_init(void)
{
    timeslice_task_init(&task_1, task1_hdl, 1, 10);
    timeslice_task_init(&task_2, task2_hdl, 2, 20);
    timeslice_task_init(&task_3, task3_hdl, 3, 30);
    timeslice_task_init(&task_4, task4_hdl, 4, 40);
    timeslice_task_init(&task_5, task5_hdl, 5, 50);
    timeslice_task_add(&task_1);
    timeslice_task_add(&task_2);
    timeslice_task_add(&task_3);
    timeslice_task_add(&task_4);
    timeslice_task_add(&task_5);
}

int main(void)
{
    teacher_t list_head;
    ListObj *pos, *next;

    list_init(&list_head.list);

    for (int i = 0; i < 5; i++)
    {
        teacher_t *p_teacher = (teacher_t*)malloc(sizeof(teacher_t));
        p_teacher->common.age = (i + 1) * 10;
        sprintf(p_teacher->common.name, "%d", i + 1);
        list_insert_before(&(list_head.list), &(p_teacher->list));
    }

    for (int i = 0; i < 5; i++)
    {
        student_t* p_student = (student_t*)malloc(sizeof(student_t));
        p_student->common.age = (i + 1) * 100;
        sprintf(p_student->common.name, "%d", i + 6);
        list_insert_before(&(list_head.list), &(p_student->list));
    }

    printf("=====List iterator=====\r\n");
    list_for_each(pos, &list_head.list)
    {
        person_t* p_person = (person_t*)list_entry(pos, teacher_t, list);
        printf("name: %-2s, common.age: %d\r\n", p_person->name, p_person->age);
    }

    task_init();
    printf(">> task num: %d\n", timeslice_get_task_num());
    printf(">> task len: %d\n", timeslice_get_task_timeslice_len(&task_3));

    timeslice_task_del(&task_2);
    printf(">> delet task 2\n");
    printf(">> task 2 is exist: %d\n", timeslice_task_isexist(&task_2));
    printf(">> task num: %d\n", timeslice_get_task_num());

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, timeslice_exec_thread, NULL);
    pthread_create(&thread2, NULL, timeslce_exec_thread, NULL);
    printf("Thread create\r\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Task init\r\n");

    return 0;
}
