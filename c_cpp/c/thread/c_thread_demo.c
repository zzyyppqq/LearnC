//
// Created by 张宜鹏 on 2022/4/19.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/prctl.h>

int g_number = 0;

#define MAX_COUNT 10000

#define NAMELEN 16

//pthread_mutex_t mut;

#define zyp_mutex_init    pthread_mutex_init
#define zyp_mutex_lock    pthread_mutex_lock
#define zyp_mutex_unlock  pthread_mutex_unlock
#define zyp_mutex_destroy pthread_mutex_destroy


void test() {
//    pthread_mutex_init();
//    pthread_mutex_lock();
//    pthread_mutex_unlock();
//    pthread_mutex_destroy();
//    zyp_mutex_init();
}

void *counter3(void* args) {
    pthread_setname_np("thread_3");
    char thread_name[NAMELEN];
    pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    printf("cur thread name: %s\n", thread_name);

    int i = 1;
    while (i <= MAX_COUNT / 4) {
        //pthread_mutex_lock(&mut);
        g_number++;
        //pthread_mutex_unlock(&mut);
        printf("hi,i am pthread 3, my g_number is [%d]\n", g_number);
        sleep(1);// 单位ms
        i++;
    }
}

void *counter4(void* args) {
    pthread_setname_np("thread_4");
    char thread_name[NAMELEN];
    pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    printf("cur thread name: %s\n", thread_name);

    int j = 1;
    while (j <= MAX_COUNT / 4) {
        //pthread_mutex_lock(&mut);
        g_number++;
        //pthread_mutex_unlock(&mut);
        printf("hi,i am pthread 4, my g_number is [%d]\n", g_number);
        sleep(1);
        j++;
    }
}


int main() {
    char thread_name[NAMELEN];
    pthread_setname_np("main_thread");
    int rc = pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    if (rc == 0) {
        printf("main thread name: %s\n", thread_name);
    }
    //pthread_mutex_init(&mut, NULL);
    pthread_t t3;
    pthread_t t4;
    pthread_create(&t3, NULL, counter3, NULL);
    pthread_create(&t4, NULL, counter4, NULL);

    sleep(3);
    if (pthread_getname_np(t3, thread_name, NAMELEN) == 0) {
        printf("t3 thread name: %s\n", thread_name);
    }
    if (pthread_getname_np(t4, thread_name, NAMELEN) == 0) {
        printf("t4 thread name: %s\n", thread_name);
    }

    getchar();
    return 0;
}