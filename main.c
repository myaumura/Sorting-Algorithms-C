//
//  main.c
//  lab5
//
//  Created by Kirill Gusev on 23.12.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 600000
#define STR_SIZE 50

void swap(int *a, int *b);
void bubble_sort(int  *arr, int size, unsigned long long int *cmp_count, unsigned long long int *swap_count);
void shaker_sort(int *arr, int size, unsigned long long int *cmp_count, unsigned long long int *swap_count);
void quick_sort(int *s_arr, int first, int last, unsigned long long int *cmp_count, unsigned long long int *swap_count);

FILE *log_data;

int main(void) {
    
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = localtime(&now);
    
    char sign;
    int flag = 0;
    char log_data_name[STR_SIZE];
    char result_name[STR_SIZE];
    char characteristics_name[STR_SIZE];
    char input_name[150];
    int arr_b[ARR_SIZE] = {0}, arr_s[ARR_SIZE] = {0}, arr_q[ARR_SIZE] = {0};
    
    // Format name files to date
    strftime(log_data_name, STR_SIZE, "log_data_%M_%H_%d_%m_%y.txt", timenow);
    strftime(result_name, STR_SIZE, "result_%M_%H_%d_%m_%y.txt", timenow);
    strftime(characteristics_name, STR_SIZE, "characteristics_%M_%H_%d_%m_%y.txt", timenow);

    FILE *infile;
    log_data = fopen(log_data_name, "w");
    fprintf(log_data, "Open log data file\n");
    
    printf("Do you have input file? y/n \n");
    fprintf(log_data, "Do you have input file? y/n\n");
    
    scanf("%c", &sign);
    fprintf(log_data, "%c\n", sign);
    
    
    if (sign == 'y') {
        printf("Input path to input file:");
        fprintf(log_data, "Input path to input file: ");
        scanf("%s", input_name);
        fprintf(log_data, "%s\n", input_name);
        flag = 1;
    } else {
        flag = 0;
    }
    
   
    int size = 0;
    
    switch (flag) {
        case 1:
            infile = fopen(input_name, "r");
            fprintf(log_data, "Open input file\n");
            
            fprintf(log_data, "Scanning array from input file\n");
            fprintf(log_data, "Scanning...\n");
            while (!feof(infile)) {
                fscanf(infile, "%d", &arr_b[size]);
                size++;
            }
            fprintf(log_data, "Scanning complete\n");
            size--;
            
            
            if (infile == NULL) {
                printf("Fatal Error: Missing input file");
            }
            fclose(infile);
            fprintf(log_data, "Close input file\n");
            break;
            
        case 0:
            printf("Input size of array: ");
            fprintf(log_data, "Input size of array: \n");
            scanf("%d", &size);
            fprintf(log_data, "%d\n", size);
            fprintf(log_data, "Creates random %d number\n", size);
            fprintf(log_data, "Randoming...\n");
            for(int i = 0; i < size; i++) {
                arr_b[i] = rand()%10000;
            }
            fprintf(log_data, "Random complete\n");
            break;
    }

    FILE *result = fopen(result_name, "w");
    fprintf(log_data, "Open result file\n");
    FILE *characteristics = fopen(characteristics_name, "w");
    fprintf(log_data, "Open characteristics file\n");
    
    
    fprintf(log_data, "Copying array\n");
    fprintf(log_data, "Copying...\n");
    for(int i = 0; i < size; i++) {
        arr_s[i] = arr_b[i];
        arr_q[i] = arr_b[i];
    }
    fprintf(log_data, "Copying finished\n");
    
    unsigned long long int bubble_cmp_count = 0;
    unsigned long long int shaker_cmp_count = 0;
    unsigned long long int quick_cmp_count = 0;
    unsigned long long int bubble_swap_count = 0;
    unsigned long long int shaker_swap_count = 0;
    unsigned long long int quick_swap_count = 0;
    
    clock_t time_bubble, time_shaker, time_quick;
    
    fprintf(log_data, "Bubble sort started\n");
    time_bubble = clock();
    bubble_sort(arr_b, size, &bubble_cmp_count, &bubble_swap_count);
    time_bubble = clock() - time_bubble;
    unsigned long long int bubble_time = (unsigned long long int)time_bubble * 1000;
    fprintf(log_data, "Bubble sort complete\n");
    fprintf(log_data, "Total compares: %llu\n", bubble_cmp_count);
    fprintf(log_data, "Total swaps: %llu\n", bubble_swap_count);
    fprintf(log_data, "Time Bubble Sort: %llu\n", bubble_time);
    
    fprintf(log_data, "Shaker sort started\n");
    time_shaker = clock();
    shaker_sort(arr_s, size, &shaker_cmp_count, &shaker_swap_count);
    time_shaker = clock() - time_shaker;
    unsigned long long int shaker_time = (unsigned long long int)time_shaker * 1000;
    fprintf(log_data, "Shaker sort complete\n");
    fprintf(log_data, "Total compares: %llu\n", shaker_cmp_count);
    fprintf(log_data, "Total swaps: %llu\n", shaker_swap_count);
    fprintf(log_data, "Time Shaker Sort: %llu\n", shaker_time);
    
    fprintf(log_data, "Quick sort started\n");
    time_quick = clock();
    quick_sort(arr_q, 0, size - 1, &quick_cmp_count, &quick_swap_count);
    time_quick = clock() - time_quick;
    unsigned long long int quick_time = (int)time_quick * 1000;
    fprintf(log_data, "Quick sort complete\n");
    fprintf(log_data, "Total compares: %llu\n", quick_cmp_count);
    fprintf(log_data, "Total swaps: %llu\n", quick_swap_count);
    fprintf(log_data, "Time Quick Sort: %llu\n", quick_time);
    
    // MARK: - Результаты сортировок
    
    // bubble sort
    for(int i = 0; i < size; i++) {
        fprintf(result, "%d ", arr_b[i]);
    }
    fprintf(result, "\n");
    
    // shaker sort
    for(int i = 0; i < size; i++) {
        fprintf(result, "%d ", arr_s[i]);
    }
    fprintf(result, "\n");
    
    // quick sort
    for(int i = 0; i < size; i++) {
        fprintf(result, "%d ", arr_q[i]);
    }
    fprintf(result, "\n");
    
    // MARK: - Characteristics
    fprintf(characteristics, "Bubble Sort:\t %llu\t %llu\t %llu\n", bubble_cmp_count, bubble_swap_count, bubble_time);
    fprintf(characteristics, "Shaker Sort:\t %llu\t %llu\t %llu\n", shaker_cmp_count, shaker_swap_count, shaker_time);
    fprintf(characteristics, "Quick Sort:\t %llu\t %llu\t %llu\n", quick_cmp_count, quick_swap_count, quick_time);
    
    // MARK: - File
    
    fclose(result);
    fprintf(log_data, "Result file closed\n");
    fclose(characteristics);
    fprintf(log_data, "Characteristics file closed\n");
    fprintf(log_data, "Log data file closed\n");
    fclose(log_data);
    
    return 0;
}

// MARK: - Функция swap

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// MARK: - Сортировка пузырьком

void bubble_sort(int *arr, int size, unsigned long long int *cmp_count, unsigned long long int *swap_count) {
    
    unsigned long long int temp_cmp = 0;
    unsigned long long int temp_swap = 0;
    
    for(int i = 0 ; i < size - 1; i++) {
        for(int j = 0 ; j < size - i - 1 ; j++) {
            if(arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j + 1]);
//                fprintf(log_data, "Bubble sort: Element moved from %d to %d\n", j, j + 1);
                temp_swap += 3;
            }
            temp_cmp++;
        }
    }
    *cmp_count = temp_cmp;
    *swap_count = temp_swap;
}

// MARK: - Шейкерная сортировка

void shaker_sort(int *arr, int size, unsigned long long int *cmp_count, unsigned long long int *swap_count) {
    int left = 0;
    int right = size - 1;
    int last_swap;
    long long int temp_cmp = 0;
    long long int temp_swap = 0;
    
    while (left < right) {
        last_swap = 0;
        
        for (int i = left; i < right; i++){
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                last_swap = i;
                temp_swap += 2;
            }
            temp_cmp++;
        }
        right = last_swap;
        
        for(int j = right; j > left; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(&arr[j], &arr[j - 1]);
                last_swap = j;
                temp_swap += 2;
            }
            temp_cmp++;
        }
        left = last_swap;
    }
    *cmp_count = temp_cmp;
    *swap_count = temp_swap;
}

// MARK: - Быстрая сортировка(Хоара)

void quick_sort(int* s_arr, int first, int last, unsigned long long int *cmp_count, unsigned long long int *swap_count) {
    
    int i = first, j = last, x = s_arr[(first + last) / 2];
    long long int temp_cmp = *cmp_count;
    long long int temp_swap = *swap_count;
    
    while (i <= j) {
        for(; s_arr[i] < x; i++) temp_cmp++;
        if (s_arr[i] >= x) temp_cmp++;
        for(; s_arr[j] > x; j--) temp_cmp++;
        if (s_arr[j] <= x) temp_cmp++;
        if(i <= j) {
            swap(&s_arr[i], &s_arr[j]);
            temp_swap += 2;
            i++;
            j--;
        }
    }
    *cmp_count = temp_cmp;
    *swap_count = temp_swap;
    
    if (i < last)
        quick_sort(s_arr, i, last, cmp_count, swap_count);
    if (first < j)
        quick_sort(s_arr, first, j, cmp_count, swap_count);
}
