typedef struct {
    int row;
    int col;
} ThreadArg;


void* computeSum(void* args) {
    ThreadArg *arg = (ThreadArg *)args;
    int i = arg->row, j = arg->col;
    matSumResult[i][j] = matA[i][j] + matB[i][j];
    free(arg);
    return NULL;
}

void* computeDiff(void* args) {
    ThreadArg *arg = (ThreadArg *)args;
    int i = arg->row, j = arg->col;
    matDiffResult[i][j] = matA[i][j] - matB[i][j];
    free(arg);
    return NULL;
}

void* computeProduct(void* args) {
    ThreadArg *arg = (ThreadArg *)args;
    int i = arg->row, j = arg->col;
    matProductResult[i][j] = 0;
    for (int k = 0; k < MAX; k++) {
        matProductResult[i][j] += matA[i][k] * matB[k][j];
    }
    free(arg);
    return NULL;
}


int main(int argc, char *argv[]) {
    srand(time(0));  // Do Not Remove.

    // 0. Get the matrix size from the command line and assign it to MAX
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix size>\n", argv[0]);
        return 1;
    }
    MAX = atoi(argv[1]);

    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);

    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);

    // 3. Create pthread_t objects for our threads.
    pthread_t threads[MAX * MAX];
    int threadNum = 0;

    // 4. Create a thread for each cell of each matrix operation.
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            ThreadArg *arg = malloc(sizeof(ThreadArg));
            arg->row = i;
            arg->col = j;
            pthread_create(&threads[threadNum++], NULL, computeSum, arg);

            arg = malloc(sizeof(ThreadArg));
            arg->row = i;
            arg->col = j;
            pthread_create(&threads[threadNum++], NULL, computeDiff, arg);

            arg = malloc(sizeof(ThreadArg));
            arg->row = i;
            arg->col = j;
            pthread_create(&threads[threadNum++], NULL, computeProduct, arg);
        }
    }

    // 5. Wait for all threads to finish.
    for (int i = 0; i < threadNum; i++) {
        pthread_join(threads[i], NULL);
    }

    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);

    return 0;
}
