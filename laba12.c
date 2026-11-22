#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <locale.h>
#include <windows.h>

#define MY_SIZEOF(type) ((size_t)((char*)((type*)0 + 1) - (char*)((type*)0)))

void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void task1(void) {
    char c = 'A', * pc = &c;
    int i = 5, * pi = &i;
    double d = 3.14, * pd = &d;

    printf("\n--- Задание 1: Размер указателей в памяти ---\n");
    printf("sizeof(char*)   = %zu байт (размер самого char   = %zu байт)\n", sizeof(pc), sizeof(c));
    printf("sizeof(int*)    = %zu байт (размер самого int    = %zu байт)\n", sizeof(pi), sizeof(i));
    printf("sizeof(double*) = %zu байт (размер самого double = %zu байт)\n", sizeof(pd), sizeof(d));
    printf("Вывод: размер любого указателя одинаков и зависит от разрядности ОС (4 или 8 байт).\n");
}

void task2(void) {
    float PI = 3.14159f, * p1, * p2;
    p1 = p2 = &PI;

    printf("\n--- Задание 2: Два указателя на одну переменную ---\n");
    printf("По адресу p1 = %p (hex: %llx) хранится *p1 = %g\n", (void*)p1, (unsigned long long)(uintptr_t)p1, *p1);
    printf("По адресу p2 = %p (hex: %llx) хранится *p2 = %g\n", (void*)p2, (unsigned long long)(uintptr_t)p2, *p2);
    printf("Вывод: оба указателя хранят один и тот же адрес переменной PI и обращаются к одному значению.\n");
}

#define TEST_PTR_STEP(type, init_val, fmt) do { \
    type val = (init_val); \
    type *ptr = &val; \
    void *start_addr = (void*)ptr; \
    ptr++; \
    ptrdiff_t diff = (char*)ptr - (char*)start_addr; \
    ptr--; \
    printf("%-18s | нач. адрес: %p | смещение при ptr++: %+td байт | *ptr = " fmt "\n", \
           #type, start_addr, diff, *ptr); \
} while (0)

void task3(void) {
    printf("\n--- Задание 3: Смещение указателя при ptr++ и ptr-- ---\n");
    TEST_PTR_STEP(int, 5, "%d");
    TEST_PTR_STEP(double, 12.34, "%g");
    TEST_PTR_STEP(char, 'Z', "%c");
    TEST_PTR_STEP(long double, 1.2345L, "%Lg");
    TEST_PTR_STEP(unsigned short int, 100, "%hu");
    TEST_PTR_STEP(_Bool, true, "%d");
    printf("Вывод: инкремент ptr++ увеличивает адрес ровно на sizeof(тип) байт.\n");
}

void task4(void) {
    float array[10] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.1f };
    float* ptr_a;

    printf("\n--- Задание 4: Работа с массивом через указатель ---\n");

    printf("4.1 Адреса начала массива:\n");
    printf("    array     = %p\n", (void*)array);
    printf("    &array[0] = %p\n", (void*)&array[0]);
    printf("    &array    = %p\n", (void*)&array);

    ptr_a = array;
    printf("\n4.2 Операции с указателем:\n");
    printf("    Начало (ptr_a):       адрес = %p, *ptr_a = %.1f\n", (void*)ptr_a, *ptr_a);
    ptr_a++;
    printf("    После ptr_a++:        адрес = %p, *ptr_a = %.1f\n", (void*)ptr_a, *ptr_a);
    printf("    Выражение ptr_a + 4:  адрес = %p, *(ptr_a + 4) = %.1f\n", (void*)(ptr_a + 4), *(ptr_a + 4));
    printf("    Выражение ptr_a - 1:  адрес = %p, *(ptr_a - 1) = %.1f\n", (void*)(ptr_a - 1), *(ptr_a - 1));
    ptr_a += 4;
    printf("    После сдвига на +4 и ptr_a - 2: адрес = %p, *(ptr_a - 2) = %.1f\n", (void*)(ptr_a - 2), *(ptr_a - 2));

    printf("\n4.3 Прямой проход с шагом +2:\n    ");
    for (ptr_a = array; ptr_a < array + 10; ptr_a += 2) {
        printf("%.1f ", *ptr_a);
    }
    printf("\n");

 
    printf("\n4.4 Обратный проход с декрементом (ptr_a--):\n    ");
    for (ptr_a = array + 9; ptr_a >= array; ptr_a--) {
        printf("%.1f ", *ptr_a);
    }
    printf("\n");
}

void print_bytes(const void* data, size_t size) {
    const unsigned char* byte_ptr = (const unsigned char*)data;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", byte_ptr[i]);
    }
    printf("\n");
}


void task5(void) {
    printf("\n--- Задание 5: Побайтовый вывод в памяти ---\n");

    unsigned int test_word = 0x11223344;
    unsigned char* first_byte = (unsigned char*)&test_word;
    printf("1. Тестовое слово 0x11223344 в памяти по возрастанию адресов: ");
    print_bytes(&test_word, sizeof(test_word));
    if (*first_byte == 0x44) {
        printf("   Порядок байтов: Little-endian (младший байт по младшему адресу).\n");
    }
    else {
        printf("   Порядок байтов: Big-endian (старший байт по младшему адресу).\n");
    }

  
    int i_val = 12345;
    float f_val = 12345.0f;
    double d_val = 12345.0;

    printf("\n2-3. Сравнение представления числа 12345 в памяти:\n");
    printf("   int    (12345)   [%zu байт]: ", sizeof(i_val));
    print_bytes(&i_val, sizeof(i_val));

    printf("   float  (12345.0) [%zu байт]: ", sizeof(f_val));
    print_bytes(&f_val, sizeof(f_val));

    printf("   double (12345.0) [%zu байт]: ", sizeof(d_val));
    print_bytes(&d_val, sizeof(d_val));
}

// дз
void task_hw(void) {
    printf("\n--- Домашнее задание\n");
    printf("1)  char               = %zu байт\n", MY_SIZEOF(char));
    printf("2)  short int          = %zu байт\n", MY_SIZEOF(short int));
    printf("3)  unsigned short int = %zu байт\n", MY_SIZEOF(unsigned short int));
    printf("4)  int                = %zu байт\n", MY_SIZEOF(int));
    printf("5)  unsigned char      = %zu байт\n", MY_SIZEOF(unsigned char));
    printf("6)  wchar_t            = %zu байт\n", MY_SIZEOF(wchar_t));
    printf("7)  long long int      = %zu байт\n", MY_SIZEOF(long long int));
    printf("8)  size_t             = %zu байт\n", MY_SIZEOF(size_t));
    printf("9)  float              = %zu байт\n", MY_SIZEOF(float));
    printf("10) double             = %zu байт\n", MY_SIZEOF(double));
    printf("11) signed int         = %zu байт\n", MY_SIZEOF(signed int));
}

int main(void) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_NUMERIC, "C");

    int choice;

    while (1) {
        printf("\n================ МЕНЮ: ЛР №12 (Указатели) ================\n");
        printf("1 - Задание 1 (размер указателей char*, int*, double*)\n");
        printf("2 - Задание 2 (два указателя на переменную PI)\n");
        printf("3 - Задание 3 (смещение указателей при ptr++ и ptr--)\n");
        printf("4 - Задание 4 (перемещение по массиву через указатель)\n");
        printf("5 - Задание 5 (побайтовый вывод и порядок байтов)\n");
        printf("6 - Домашнее задание  \n");
        printf("0 - Выход\n");
        printf("Выберите пункт меню: ");

        if (scanf("%d", &choice) != 1) {
            clear_input();
            printf("Ошибка ввода! Введите число от 0 до 6.\n");
            continue;
        }
        clear_input();

        if (choice == 0) {
            printf("Выход из программы.\n");
            break;
        }

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task_hw(); break;
        default:
            printf("Неверный пункт меню!\n");
            continue;
        }
        system("pause");
    }

    return 0;
}
