#include <iostream>
#include <time.h> 
#include <malloc.h>
#include <math.h>
using namespace std;

void print_matrix(double** matrix, int n, string name){
    cout << "\n\t\t\t     Матрица " << name << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.16lf\t", matrix[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

double** make_arr(int n, int v, char name) {
    double** new_arr = new double* [n];
    for (int i = 0; i < n; i++)
        new_arr[i] = new double[n];
    if (name == 'A'){
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) {
                new_arr[i-1][j-1] = (cos(0.2 * i) - sin(0.3 * j))/v;
            }
        }
    }
    else if (name == 'B'){
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++) {
                new_arr[i-1][j-1] = (sin(0.7 * i) - cos(0.4 * j))/v;
            }
        }
    }
    return new_arr;
}

void linear_sum_arr(float &s1, double &s2, double** c, int N){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            s1 += (float)c[i][j];
        }
    }
    //cout << s1 << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            s2 += c[i][j];
        }
    }
    //cout << s2 << endl;
}

void mult(double** x, double** y, double** mt, int n){
    double temp = 0;
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                    for(int k = 0; k < n; k++)
                    {
                            temp += x[j][k] * y[k][j];
                            //cout << x[j][k] * y[k][j] <<endl;
                    }
                    mt[i][j] = temp;
                    //cout << endl << temp << endl << endl << endl;
            }
        }
    }
}

void transpose(double** matrix, int n)
{
    double t;
    for(int i = 0; i < n; ++i)
    {
        for(int j = i; j < n; ++j)
        {
            t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
}

void sum_arr(int V, bool is_need_transpose){
    clock_t start1 = clock();
    int N = 6;
    double** A;
    A = make_arr(N, V, 'A');
    double** B;
    B = make_arr(N, V, 'B');
    if (is_need_transpose) {
        transpose(B, N);
    }
    double** C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    //print_matrix(A, N, "A");
    float single_sum = 0;
    double double_sum = 0;
    linear_sum_arr(single_sum, double_sum, C, N);
    //cout << "single sum = " << single_sum << "\tdouble sum = " << double_sum << endl;
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("N = %d\nСумма элементов с одинарной точностью: %.8f\n", N, single_sum);
    printf("Сумма элементов с двойной точностью: %.16lf\nВремя: %.8f\n\n", double_sum, seconds1);
    for (int i = 0; i < N; i++)
        {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
        }
    delete[] A;
    delete[] B;
    delete[] C;
    
    clock_t start2 = clock();
    N = 300;
    A = make_arr(N, V, 'A');
    B = make_arr(N, V, 'B');
    if (is_need_transpose) {
        transpose(B, N);
    }
    C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    //print_matrix(A, N, "A");
    single_sum = 0;
    double_sum = 0;
    linear_sum_arr(single_sum, double_sum, C, N);
    //cout << "single sum = " << single_sum << "\tdouble sum = " << double_sum << endl;
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("N = %d\nСумма элементов с одинарной точностью: %.8f\n", N, single_sum);
    printf("Сумма элементов с двойной точностью: %.16lf\nВремя: %.4f\n\n", double_sum, seconds2);
    for (int i = 0; i < N; i++)
        {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
        }
    delete[] A;
    delete[] B;
    delete[] C;

    clock_t start3 = clock();
    N = 900;
    A = make_arr(N, V, 'A');
    B = make_arr(N, V, 'B');
    if (is_need_transpose) {
        transpose(B, N);
    }
    C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    //print_matrix(A, N, "C");
    single_sum = 0;
    double_sum = 0;
    linear_sum_arr(single_sum, double_sum, C, N);
    //cout << "single sum = " << single_sum << "\tdouble sum = " << double_sum << endl;
    clock_t end3 = clock();
    double seconds3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf("N = %d\nСумма элементов с одинарной точностью: %.8f\n", N, single_sum);
    printf("Сумма элементов с двойной точностью: %.16lf\nВремя: %.4f\n\n", double_sum, seconds3);
    for (int i = 0; i < N; i++)
        {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
        }
    delete[] A;
    delete[] B;
    delete[] C;
}


int main()
{

    // V по варианту
    int const V = 4;

    // Лаба №3
    cout << "Лабораторная работа №3\n\n";
    
    cout << "Задание 1\nУмножение матрицы A на B \"строка на столбец\"" << endl;
    int N;
    cout << "Введите N = ";
    cin >> N;
    double** A; //указатель для массива указателей
    //clock_t startA = clock();
    A = make_arr(N, V, 'A');
    //clock_t endA = clock();
    //double secondsA = (double)(endA - startA) / CLOCKS_PER_SEC;
    //printf("Массив заполняется за %.2f\n", secondsA);
    
    double** B; //указатель для массива указателей
    //clock_t startB = clock();
    B = make_arr(N, V, 'B');
    // clock_t endB = clock();
    // double secondsB = (double)(endB - startB) / CLOCKS_PER_SEC;
    // printf("Массив заполняется за %.4f\n", secondsB);

    // print_matrix(A, N);
    // cout << endl;
    // print_matrix(B, N);

    double** C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    print_matrix(C, N, "C");
    for (int i = 0; i < N; i++)
        {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
        }
    delete[] A;
    delete[] B;
    delete[] C;
    // Задание №2
    cout << "Задание №2" << endl;
    sum_arr(V, false);


    // Задание №3
    N = 6;
    printf("\n\nЗадание №3\nПри N = %d вывести массивы A, B и С = A*B\n", N);
    A = make_arr(N, V, 'A');
    B = make_arr(N, V, 'B');
    C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    print_matrix(A, N, "A");
    print_matrix(B, N, "B");
    print_matrix(C, N, "C");
    for (int i = 0; i < N; i++)
        {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
        }
    delete[] A;
    delete[] B;
    delete[] C;
    // Лаба 3 закончена






    // Лаба 4
    cout << "\n\nЛаба 4\n";
    // Задание №1
    cout << "Задание №1\nТранспонировать матрицу B\nN = ";
    cin >> N;
    B = make_arr(N, V, 'B');
    print_matrix(B, N, "B");
    transpose(B, N);
    print_matrix(B, N, "B, транспонированная");
    
    // Задание №2
    cout << "Задание №2\nУмножить матрицу A на B (транспонированную)\n";
    A = make_arr(N, V, 'A');
    C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    print_matrix(C, N, "C");

    // Задание №3
    cout << "Задание №3" << endl;
    sum_arr(V, true);

    // Задание №4
    cout << "Задание №4\n Вывести матрицы" << endl;
    N = 6;
    cout << "N = " << N << endl;
    A = make_arr(N, V, 'A');
    B = make_arr(N, V, 'B');
    transpose(B, N);
    C = make_arr(N, V, 'C');
    mult(A, B, C, N);
    print_matrix(A, N, "A");
    print_matrix(B, N, "B, транспонированная");
    print_matrix(C, N, "C");
    return 0;
}
