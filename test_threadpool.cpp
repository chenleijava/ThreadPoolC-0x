//
// Created by chenlei on 9/8/16.
//

#include "ThreadPool.h"

#include "stdio.h"

int main() {

    ThreadPool threadPool(2);
    for (int i = 0; i < 100; ++i) {
        threadPool.add([&] {
            printf("test%d !!!!!!\n",i);
        });
    }

    return 0;
}
