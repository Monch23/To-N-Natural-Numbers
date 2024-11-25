#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int *data;
    size_t size;

} Info;

int isNatural(int num) {
    if (num == 2) { return 1; }

    int tmpNum = num - 1;

    while (tmpNum >=2) {
        if (!(num % tmpNum--)) {
            return 0;
        }
    }

    return 1;
}

void *to_n_natural_numbers(void *structure) {
    Info *info = (Info*)structure;
    int n;
    size_t tmpN = 2;

    puts("Input < n >");
    scanf("%d", &n);
    if (n < 2) {
        puts("Number is lower than 2");
        exit(EXIT_FAILURE);
    }

    info->data = (int*)malloc(n * sizeof(int));

    while (tmpN <= n) {
        if (isNatural(tmpN)) {
            info->data[info->size++] = tmpN;
        }
        ++tmpN;
    }

    return NULL;
}

void *freeMem(void *memory) {
    system("clear");
    Info *mem = (Info*)memory;
    usleep(55000);

    for (size_t i = 0; i < mem->size; ++i) {
        printf("memory[%zu]=%d \n", i, mem->data[i]);
    }

    free(mem->data);
    return NULL;
}

int main() {
    pthread_t thr1, thr2;
    Info info;
    info.size = 0;

    pthread_create(&thr1, NULL, to_n_natural_numbers, (void*)&info);
    pthread_join(thr1, NULL);
    pthread_create(&thr2, NULL, freeMem, (void*)&info);
    pthread_join(thr2, NULL);

    return 0;
}