#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREADNUM 5
#define COUNT_TARGET 20
// 全局变量sem
sem_t *sem;
// 全局计数器
int count;
// 线程任务
void *print(void *arg) {
    int no = *(int *)arg;
    while (count < COUNT_TARGET) {
        // p
        sem_wait(sem);
        if (count < COUNT_TARGET) {
            printf("no.%d p......\n", no);
            count++;
            printf("thread no.%d, count:%d\n", no, count);
            usleep(20000);
            printf("no.%d v.......\n", no);
        }
        // v
        sem_post(sem);
    }
   return NULL; 
}
int main() {
    // init
    int res;
    count = 0;
    sem = sem_open("demo", 0);
    // new threads
    pthread_t thread[THREADNUM];
    int arg[THREADNUM];
    for (int i = 0; i < THREADNUM; ) {
        arg[i] = i;
        res = pthread_create(&thread[i], NULL, print, &arg[i]);
        if (res != 0) {
            printf("create thread failed.\n");
            exit(0);
        }
        i++;
    }
    sem_post(sem);
    for (int i = 0; i < THREADNUM; i++) {
        pthread_join(thread[i], NULL);
    }
    // release mutex
    printf("close semaphore...\n");
    sem_close(sem);
}
