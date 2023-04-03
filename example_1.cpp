#include <iostream>
#include <string>
#include <time.h> 
#include <malloc.h>
using namespace std;

void info_message(float single_s1, float single_s2, float single_s3,
    double double_s1, double double_s2, double double_s3) {
    printf("   Одинарная / Двойная точность\nS1 : %.8f\t%.16lf\nS2 : %.8f\t%.16lf\nS3 : %.8f\t%.16lf\n", single_s1, double_s1, single_s2, double_s2, single_s3, double_s3);
    //cout << "   Одинарная / Двойная точность" <<
    //    "\nS1 : " << single_s1 << "\t" << double_s1 <<
    //    "\nS2 : " << single_s2 << "\t" << double_s2 <<
    //    "\nS3 : " << single_s3 << "\t" << double_s3 << "\n";
}

void abs_sort(double* m, int n)
{
    for (int i = n - 1; i >= 1; i--)
        for (int j = 0; j < i; j++)
        {
            if (abs(m[j]) > abs(m[j + 1]))
            {
                double foo = m[j];
                m[j] = m[j + 1];
                m[j + 1] = foo;
            }
        }
}

void get_sum_S_single(double A[], int n, float& s1, float& s2, float& s3) {
    s1 = 0, s2 = 0, s3 = 0;
    for (int i = 0; i < n; i++) {
        s1 += (float)A[i];
    }
    // TODO добавить сортировку массива
    abs_sort(A, n);
    for (int i = 0; i < n; i++) {
        s2 += (float)A[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        s3 += (float)A[i];
    }
}

void get_sum_S_dobule(double A[], int n, double& s1, double& s2, double& s3) {
    s1 = 0, s2 = 0, s3 = 0;
    for (int i = 0; i < n; i++) {
        s1 += A[i];
    }
    // TODO добавить сортировку массива
    abs_sort(A, n);
    for (int i = 0; i < n; i++) {
        s2 += A[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        s3 += A[i];
    }
}

double* make_arr(int n, int v) {
    double* new_arr = new double[n];
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            new_arr[i - 1] = (i + 1.0) * sin(v + i);
        }
        else {
            new_arr[i - 1] = (1.0 / (i + 1.0)) * cos(v + i);
        }
    }

    return new_arr;
}

int main()
{
    /*cout.precision(10);*/
    int n;
    cout << "Введите N: ";
    cin >> n;
    int v = 4;
    double* A = make_arr(n, v);
    cout << A[0] << endl;
    cout << A[1] << endl;
    cout << A[2] << endl;
    float single_s1, single_s2, single_s3;
    double double_s1, double_s2, double_s3;
    get_sum_S_single(A, n, single_s1, single_s2, single_s3);
    get_sum_S_dobule(A, n, double_s1, double_s2, double_s3);

    info_message(single_s1, single_s2, single_s3, double_s1, double_s2, double_s3);
    double diff_near_s1 = abs(single_s1 - double_s1);
    double diff_near_s2 = abs(single_s2 - double_s2);
    double diff_near_s3 = abs(single_s3 - double_s3);

    cout << "Разница между точностями:\n(S1-S1)\t\t(S2-S2)\t\t(S3-S3)\n" << diff_near_s1 << "\t" << diff_near_s2 << "\t" << diff_near_s3 << endl;
    cout << "\n\n";
    // Для N = 12
    //delete[] &A;

    n = 12;
    double* A12 = make_arr(n, v);
    cout << "Для N = 12" << endl;
    cout << "\nИсходный массив" << endl;
    for (int i = 0; i < n; i += 2) {
        printf("%.16lf\t%.16lf\n", A12[i], A12[i + 1]);
        //cout << A12[i] << "\t" << A12[i + 1] << endl;
    }
    abs_sort(A12, n);
    cout << "\nОтсортированный массив" << endl;
    for (int i = 0; i < n; i += 2) {
        printf("%.16lf\t%.16lf\n", A12[i], A12[i + 1]);
        //cout << A12[i] << "\t" << A12[i + 1] << endl;
    }
    cout << "\n\n";
    // Для N = 120_000 и N = 240_000

    int N1 = 120000;
    double* A1 = make_arr(N1, v);

    get_sum_S_single(A1, N1, single_s1, single_s2, single_s3);

    clock_t start1 = clock();
    get_sum_S_dobule(A1, N1, double_s1, double_s2, double_s3);
    clock_t end1 = clock();
    double seconds = (double)(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Для N = " << N1 << "\n";
    info_message(single_s1, single_s2, single_s3, double_s1, double_s2, double_s3);
    cout << "время работы = " << seconds << endl;


    int N2 = 240000;
    double* A2 = make_arr(N2, v);

    get_sum_S_single(A2, N2, single_s1, single_s2, single_s3);

    clock_t start2 = clock();
    get_sum_S_dobule(A2, N2, double_s1, double_s2, double_s3);
    clock_t end2 = clock();
    seconds = (double)(end2 - start2) / CLOCKS_PER_SEC;
    cout << "\n\nДля N = " << N2 << "\n";
    info_message(single_s1, single_s2, single_s3, double_s1, double_s2, double_s3);
    cout << "время работы = " << seconds << endl;
    return 0;
}
