#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5

pthread_mutex_t mutex;

/* void *worker_thread(void *arg)
{
        printf("This is worker_thread()\n");
        return NULL;
}
int main()
{
        pthread_t my_thread;
        int ret;
        printf("In main: creating thread\n");
        ret = pthread_create(&my_thread, NULL, &worker_thread, NULL);
        if(ret != 0)
        {
                printf("Error: pthread_create() failed\n");
        }
        pthread_join(my_thread, NULL);
        return 0;
} */

void *worker_thread(void *arg)
{
    int *res = (int *)arg;

    // pthread_mutex_lock(&mutex);
    for (int i = 0; i < 1000; i++)
    {
        (*res) += 1;
    }
    // pthread_mutex_unlock(&mutex);
}
int main(int ac, char **av)
{
    pthread_t my_thread[atoi(av[1])];

    pthread_mutex_init(&mutex, NULL);
    int dis = 0;
    long id;
    int ret;
    printf("In main: creating thread\n");
    for (id = 0; id < N; id++)
    {
        ret = pthread_create(&my_thread[id], NULL, worker_thread, (void *)&dis);
        if (ret != 0)
        {
            printf("Error: pthread_create() failed\n");
        }
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(my_thread[i], NULL);
    }
    printf("Result : %d\n", dis);
    return 0;
}