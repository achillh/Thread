#include <iostream>
#include <pthread.h>
#include <string.h>

static int result = 0;
void *start(void *str){
    int s;
    printf("hello form subthread %s \n", (char *) str);
//    s = pthread_detach(pthread_self()); 1.这里detach后 2处调用join是错误的
//    if (s == 0) {
//        printf("pthread_detach success  %d\n", s);
//    } else {
//        printf("pthread_detach failed  %d\n", s);
//
//    }
    return (void *)strlen((char *) str);
}

void *addNum(void *loopNum){
    long loop = (long) loopNum;
    for (int i = 0; i < loop; ++i) {
        result++;
    }
    return nullptr;
}

int main() {
    pthread_t pt;
    void *len;
    int s;
    s = pthread_create(&pt, nullptr, start, (void *) "params");
    if (s == 0) {
        printf("create thread success %d \n", s);
    }
    s = pthread_join(pt, &len);//2.
    if (s == 0) {
        printf("pthread join get return value %ld\n", (long)len);
    } else {
        printf("pthread join get return value %ld\n", (long)len);
    }

    pthread_t addPt1, addPt2;

    long loopNum = 100;
    s = pthread_create(&addPt1, nullptr, addNum, (void *)loopNum);
    if (s == 0) {
        printf("create addPt1 success %d \n", s);
    } else {
        printf("create addPt1 fail %d \n", s);
    }

    s = pthread_create(&addPt2, nullptr, addNum, (void *)loopNum);
    if (s == 0) {
        printf("create addPt2 success %d \n", s);
    } else {
        printf("create addPt2 fail %d \n", s);
    }

    s=pthread_join(addPt1, nullptr);
    if (s == 0) {
        printf("addPt1 terminal success %d \n", s);
    } else {
        printf("addPt1 terminal fail %d \n", s);
    }
    s=pthread_join(addPt2, nullptr);
    if (s == 0) {
        printf("addPt2 terminal success %d \n", s);
    } else {
        printf("addPt2 terminal fail %d \n", s);
    }

    printf("after add the result is %d", result);
    return 0;
}


