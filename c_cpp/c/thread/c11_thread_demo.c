////
//// Created by zhangyipeng on 2023/11/7.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <threads.h>
//
//int thread_function(void *arg) {
//    int thread_arg = *(int *)arg;
//    printf("This is the thread function. Argument passed: %d\n", thread_arg);
//    return 0;
//}
//
//int main() {
//    thrd_t my_thread;
//    int arg = 123;
//
//    // 创建线程
//    if (thrd_create(&my_thread, thread_function, &arg) != thrd_success) {
//        fprintf(stderr, "Failed to create a new thread.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Main function after thrd_create()\n");
//
//    // 等待线程结束
//    int res;
//    if (thrd_join(my_thread, &res) != thrd_success) {
//        fprintf(stderr, "Failed to join the thread.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Main function after thrd_join()\n");
//
//    return 0;
//}
