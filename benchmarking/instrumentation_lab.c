#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
    *state = (*state * 1103515245u) + 12345u;
    return (*state);
}

static void build_dataset(void)
{
    unsigned int state;
    int i;

    state = SEED_VALUE;

    for (i = 0; i < DATASET_SIZE; i++)
        dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
    int i;
    int v;

    for (i = 0; i < DATASET_SIZE; i++)
    {
        v = dataset[i];
        v = (v * 3) + (v / 7) - (v % 11);
        if (v < 0)
            v = -v;
        dataset[i] = v;
    }
}

static unsigned long reduce_checksum(void)
{
    unsigned long sum;
    int i;

    sum = 0;
    for (i = 0; i < DATASET_SIZE; i++)
        sum = (sum * 131ul) + (unsigned long)dataset[i];

    return (sum);
}

int main(void)
{
    unsigned long checksum;

clock_t start_total, end_total;
    clock_t start_p, end_p;
    double total_s, build_s, process_s, reduce_s;

    /* Début du chronométrage global */
    start_total = clock();

    /* Mesure : BUILD_DATA */
    start_p = clock();
    build_dataset();
    end_p = clock();
    build_s = (double)(end_p - start_p) / CLOCKS_PER_SEC;

    /* Mesure : PROCESS */
    start_p = clock();
    process_dataset();
    end_p = clock();
    process_s = (double)(end_p - start_p) / CLOCKS_PER_SEC;

    /* Mesure : REDUCE */
    start_p = clock();
    checksum = reduce_checksum();
    end_p = clock();
    reduce_s = (double)(end_p - start_p) / CLOCKS_PER_SEC;

    /* Fin du chronométrage global */
    end_total = clock();
    total_s = (double)(end_total - start_total) / CLOCKS_PER_SEC;
	
    build_dataset();
    process_dataset();
    checksum = reduce_checksum();

    if (checksum == 0ul)
        printf("impossible\n");

		printf("TOTAL seconds: %.6f\n", total_s);
    printf("BUILD_DATA seconds: %.6f\n", build_s);
    printf("PROCESS seconds: %.6f\n", process_s);
    printf("REDUCE seconds: %.6f\n", reduce_s);

    return (0);
}
