// Lab 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <time.h> 
#include <malloc.h>
#include <math.h>
using namespace std;

int main()
{
    int const N = 10000;
    int const V = 4;
    double** array; //указатель для массива указателей
    array = new double* [N]; //выделение динамической памяти 
    for (int i = 0; i < N; i++)
        array[i] = new double[N]; //выделение динамической памяти
    cout << "Hello World!\n";
    clock_t start = clock();
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++) {
            array[i-1][j-1] = (sin(0.2 * i) - cos(0.3 * j))/V;
        }
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив заполняется за %.2f\n", seconds);
    clock_t start1 = clock();
    double s1 = 0.0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            s1 += array[i][j];
        }
    }
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;

    clock_t start2 = clock();
    double s2 = 0.0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            s2 += array[j][i];
        }
    }
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("A11 = %.16lf\tAnn = %.16lf\nS1 = %.16lf\nS2 = %.16lf\nВремя для первой суммы: %.5f\nВремя для второй суммы: %.5f\n\n\n\n\n\n\n", array[0][0], array[N - 1][N - 1], s1, s2, seconds1, seconds2);
    //cout << "A11 = " << array[0][0] << "\tAnn = " << array[N-1][N-1] << "\nS1 = " << s1 << "\tS2 = " << s2 << "\nВремя для первой суммы: " << seconds1 << "\nВремя для второй суммы: " << seconds2;
    return 0;
}
