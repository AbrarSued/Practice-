#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shakerSort(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while (left < right&& swapped) {
        swapped = 0;

        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(&arr[i], &arr[i - 1]);
                swapped = 1;
            }
        }
        left++;

        if (!swapped) break;
    }
}

void printCentered(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    printf("+");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");
    printf("|");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < width - len - padding; i++) printf(" ");
    printf("|\n");
    printf("+");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");
}

void printArrayFromFile(const char* filename, const char* title, int width) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    printCentered(title, width - 2);

    int num, count = 0;
    while (fscanf(file, "%d", &num) == 1) {
        printf(" %5d", num);
        count++;
        if (count % 15 == 0) {
            printf("\n");
        }
    }

    if (count % 15 != 0) {
        printf("\n");
    }

    fclose(file);
}

void saveToFile(int arr[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
        if ((i + 1) % 15 == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("Массив сохранен в файл %s\n", filename);
}

int main() {
    setlocale(LC_ALL, "");
    int n, min_val, max_val;
    const int consoleWidth = 90;
    clock_t start, end;
    double time_used;

    printCentered("ШЕЙКЕРНАЯ СОРТИРОВКА", consoleWidth - 2);

    printf(" Введите размер массива: ");
    scanf("%d", &n);

    printf(" Введите минимальное значение элемента: ");
    scanf("%d", &min_val);

    printf(" Введите максимальное значение элемента: ");
    scanf("%d", &max_val);

    if (min_val > max_val) {
        printf("\nОшибка: минимальное значение не может быть больше максимального!\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("\n");
        printCentered("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ!", consoleWidth - 2);
        return 1;
    }

    srand(time(0));
    int range = max_val - min_val + 1;
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % range + min_val;
    }

    saveToFile(arr, n, "input.txt");
    printArrayFromFile("input.txt", "ИСХОДНЫЙ МАССИВ", consoleWidth);

    printf("\n");
    printCentered("НАЧАЛО СОРТИРОВКИ", consoleWidth - 2);

    start = clock();
    shakerSort(arr, n);
    end = clock();

    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n");
    printCentered("СОРТИРОВКА ЗАВЕРШЕНА", consoleWidth - 2);
    printf(" Время выполнения сортировки: %.6f секунд\n", time_used);
    printf(" Диапазон значений: [%d, %d]\n", min_val, max_val);
    printf("\n");

    saveToFile(arr, n, "sorted.txt");
    printArrayFromFile("sorted.txt", "ОТСОРТИРОВАННЫЙ МАССИВ", consoleWidth);

    free(arr);
    return 0;
}