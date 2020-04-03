#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* func(void *arg)
{
    int* ptr = (int*)arg;
    printf("%d\n", *ptr);
    return NULL;
}

int main()
{
    pthread_t th[3];
    int a[3];
    for(int i = 1; i <= 3; i++)
    {
        a[i-1]=i;
        pthread_create(&th[i-1], NULL, func, &a[i-1]);
    }
    sleep(1);
    return 0;
}
