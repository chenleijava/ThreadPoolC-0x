### 基于c++0x 实现的线程池

```
#include "ThreadPool.h"

#include "stdio.h"

int main() {

    ThreadPool threadPool(2);
    for (int i = 0; i < 3; ++i) {
        threadPool.add([&] {
            printf("test%d !!!!!!\n",i);
        });
    }

    return 0;
}

```