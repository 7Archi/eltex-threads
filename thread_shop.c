#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m[5] = {PTHREAD_MUTEX_INITIALIZER};
int shop[5] = {0};

struct deal
{
    int num;
    int val;
};

void* shopping(void* vali)
{
    struct deal *tmp = (struct deal*) vali;
    int i = rand() % 5;
    if(!pthread_mutex_trylock(&m[i]))
    {
	if(tmp->num == 3)
        {
            printf("\nLoader goes to the shop %d : %d + %d = %d\n\n", i, shop[i], (tmp->val), shop[i] + tmp->val);
            shop[i]+=tmp->val;
        }
        else
        {
            printf("Buyer %d goes to the shop %d : %d - %d = %d\n\n", tmp->num, i, tmp->val, shop[i], tmp->val - shop[i]);
            if(tmp->val >= shop[i])
            {
                tmp->val -= shop[i];
                shop[i] = 0;
            }
            else
            {
                shop[i] -= tmp->val;
                tmp->val = 0;
            }
        }
        pthread_mutex_unlock(&m[i]);
    }
    return NULL;
}

void* buyer(void *numb)
{
    int *n = (int*)numb;
    struct deal tmp;
    tmp.val = 1000;
    tmp.num = *n;
    pthread_t tid;
    while(tmp.val > 0)
    {
        pthread_create(&tid, NULL, shopping, &tmp);
        pthread_join(tid, NULL);
        sleep(2);
    }
    printf("Buyer %d is satisfied\n\n", *n);
    return NULL;
}

void* loader()
{
    int load;
    load = 200;
    struct deal tmp;
    pthread_t tid;
    while(1)
    {
        tmp.val = load;
        tmp.num = 3;
        pthread_create(&tid, NULL, shopping, &tmp);
        pthread_join(tid, NULL);
        sleep(2);
    }
    return NULL;
}

int main()
{
    for(int i = 0; i < 5; i++)
    {
        shop[i]+=200;
    }

    pthread_t th[4];
    int a[3] = {0};
    for(int i = 0; i < 3; i++)
    {
        a[i]=i;
        pthread_create(&th[i], NULL, buyer, &a[i]);
    }
    pthread_create(&th[3], NULL, loader, NULL);

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    pthread_join(th[2], NULL);
    pthread_cancel(th[3]);

    printf("It's all\n\n");
    return 0;
}
