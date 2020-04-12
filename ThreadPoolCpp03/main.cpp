#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "ThreadPool.h"

// 任务类
class MyTask {
   public:
	MyTask() {}

	int run(int i, const char* p) {
		printf("thread[%lu] : (%d, %s)\n", pthread_self(), i, (char*)p);
		sleep(1);
		return 0;
	}
};

void fuck(int i, const char* p) {
	printf("fuck thread[%lu] : (%d, %s)\n", pthread_self(), i, (char*)p);
}

int main() {
	uranus::ThreadPool threadPool(4);
	MyTask taskObj[20];
	for (int i = 0; i < 20; i++) {
		// bind是函数适配器, 减少参数
		// threadPool.addTask(std::bind(&MyTask::run, &taskObj[i], i, "helloworld"));
		threadPool.addTask(std::bind(&fuck, i, "joke"));
	}

	while (1) {
		printf("there are still %d tasks need to process\n", threadPool.size());
		if (threadPool.size() == 0) {
			threadPool.stop();
			printf("Now I will exit from main\n");
			exit(0);
		}
		sleep(2);
	}

	return 0;
}
