#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADNUM 5
#define TARGET 20
// 全局变量mutex
pthread_mutex_t mutex;
// 全局计数器
int count;
// 线程任务
void *print(void *arg) {
    int no = *(int *)arg;
    while (count < TARGET) {
        // lock
        pthread_mutex_lock(&mutex);
        if (count < TARGET) {
            printf("no.%d locking.....\n", no);
            count++;
            printf("thread no.%d, count:%d\n", no, count);
            usleep(20000);
            printf("no.%d unlocking....\n", no);
        }
        // unlock
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
// master edit
int main() {
    // init
    count = 0;
    pthread_mutex_init(&mutex, NULL);
    // new threads
    pthread_t thread[THREADNUM];
    int no[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        no[i] = i;
        int retV = pthread_create(&thread[i], NULL, print, &no[i]);
        if (retV != 0) {
            printf("create thread failed.\n");
            exit(0);
        }
    }
    for (int i = 0; i < THREADNUM; i++) {
        pthread_join(thread[i], NULL);
    }
    // release mutex
    printf("close mutex...\n");
    pthread_mutex_destroy(&mutex);
    //new branch
    //new branch
}
//new branch edit
//new branch edit
//new branch edit
