#include <iostream>
#include <time.h> 
#include <malloc.h>
#include <math.h>

using namespace std;

void print_matrix(double* &A, double* &B, double* &C, int n){
    cout << "\n\t\t\t     C\n" << endl;
    for (int i = 0; i < n; i++)
    {
        printf("%.16lf\t", C[i]);
    }
    cout << "\n\t\t\t     B\n" << endl;
    for (int i = 0; i < n; i++)
    {
        printf("%.16lf\t", B[i]);
    }
    cout << "\n\t\t\t     A\n" << endl;
    for (int i = 0; i < n; i++)
    {
        printf("%.16lf\t", A[i]);
    }
    cout << endl;
}

void print_vector(double* x, int n, string name){
    cout << "\n\t\t\t     Вектор " << name << endl;
    for (int i = 0; i < n; i++){
        printf("%.16lf\t", x[i]);
    }
    cout << endl;
}

void print_vector(float* x, int n, string name){
    cout << "\n\t\t\t     Вектор " << name << endl;
    for (int i = 0; i < n; i++){
        printf("%.16lf\t", x[i]);
    }
    cout << endl;
}

void print_vector_range(double* x, int i1, int i2, string name){
    printf("\n\t     Значения Вектора %s в диапазоне от %i до %i\n", name.c_str(), i1, i2);
    // cout << "\n\t\t\t     Значения Вектора " << name << endl;

    for (int i = i1 - 1; i < i2; i++){
        printf("%.16lf\t", x[i]);
    }
    cout << "\n";
}

void print_vector_range(float* x, int i1, int i2, string name){
    printf("\n\t     Значения Вектора %s в диапазоне от %i до %i", name.c_str(), i1, i2);
    // cout << "\n\t\t\t     Значения Вектора " << name << endl;

    for (int i = i1 - 1; i < i2; i++){
        printf("%.16lf\t", x[i]);
    }
    cout << "\n";
}

// double** make_arr(int n, int v) {
//     double** new_arr = new double* [n];
//     for (int i = 0; i < n; i++){
//         new_arr[i] = new double[n];
//         // printf("\n%i", i);
//     }
//     // Главная диагональ
//     for (int i = 0; i < n; i++)
//         new_arr[i][i] = 10*v + double(i+1)/v;
//     // Верхняя диагональ
//     for (int i = 0; i < n - 1; i++)
//         new_arr[i][i+1] = 0.4*cos(i+1)/v;
//     // Нижняя диагональ
//     for (int i = 1; i < n; i++)
//         new_arr[i][i-1] = 0.3*sin(i+1)/v;
//     return new_arr;
// }

void make_arr(double* &A, double* &B, double* &C, int n, int v) {
    double* A1 = new double[n-1];
    double* B1 = new double[n];
    double* C1 = new double[n-1];
    // Главная диагональ
    for (int i = 0; i < n; i++)
        B1[i] = 10*v + double(i+1)/v;
        // cout << "\t\t\t\t" << i << "\n\n";}
    // Верхняя диагональ
    for (int i = 0; i < n - 1; i++)
        C1[i] = 0.4*cos(i+1)/v;
    // Нижняя диагональ
    for (int i = 0; i < n - 1; i++)
        A1[i] = 0.3*sin(i+2)/v;
    A = A1;
    B = B1;
    C = C1;
}

double* make_vector(int n, int v) {
    double* new_arr = new double[n];
    for (int i = 0; i < n; i++)
        new_arr[i] = 1.3 + double(i+1)/v;
    return new_arr;
}

double* solution_double(double* A, double* B, double* C, double* b, int n){
    double* x = new double[n];
    double* v = new double[n];
    double* u = new double[n];
    // Прямой ход
    for (int i = 0; i < n; i++){
        v[i] = 0;
        u[i] = 0;
    }
    // для первой 0-й строки
    v[0] = C[0] / (-B[0]);
    u[0] = (-b[0]) / (-B[0]);
    // заполняем за исключением 1-й и (n-1)-й строк матрицы
    for (int i = 1; i < n - 1; i++){
        v[i] = C[i] / ( -B[i] - A[i-1]*v[i-1] );
        u[i] = ( A[i-1]*u[i-1] - b[i] ) / ( -B[i] - A[i-1]*v[i-1] );
    }
    // для последней (n-1)-й строки
    v[n-1] = 0;
    u[n-1] = (A[n-1]*u[n-2] - b[n-1]) / (-B[n-1] - A[n-1]*v[n-2]);

    // Обратный ход
    x[n-1] = u[n-1];
    for (int i = n-1; i > 0; i--){
        x[i-1] = v[i-1] * x[i] + u[i-1];
    }
    return x;
}

float* solution_float(double* A, double* B, double* C, double* b, int n){
    float* x = new float[n];
    float* v = new float[n];
    float* u = new float[n];
    // Прямой ход
    for (int i = 0; i < n; i++){
        v[i] = 0;
        u[i] = 0;
    }
    // для первой 0-й строки
    v[0] = C[0] / (-B[0]);
    u[0] = (-b[0]) / (-B[0]);
    // заполняем за исключением 1-й и (n-1)-й строк матрицы
    for (int i = 1; i < n - 1; i++){
        v[i] = C[i] / ( -B[i] - A[i-1]*v[i-1] );
        u[i] = ( A[i-1]*u[i-1] - b[i] ) / ( -B[i] - A[i-1]*v[i-1] );
    }
    // для последней (n-1)-й строки
    v[n-1] = 0;
    u[n-1] = (A[n-1]*u[n-2] - b[n-1]) / (-B[n-1] - A[n-1]*v[n-2]);

    // Обратный ход
    x[n-1] = u[n-1];
    for (int i = n-1; i > 0; i--){
        x[i-1] = v[i-1] * x[i] + u[i-1];
    }
    return x;
}

void norm_vector_nev(double* A, double* B, double* C, double* x, double* b, int n, bool is_need_print_vector){
    double* res = new double[n];
    res[0] = 0;
    res[0] += B[0] * x[0];
    res[0] += C[0] * x[1];
    res[n-1] = 0;
    res[n-1] += B[n-1] * x[n-1];
    res[n-1] += A[n-1] * x[n-2];
    for (int i = 1; i < n-1; i++){
        res[i] = 0;
        res[i] += A[i-1] * x[i-1];
        res[i] += B[i] * x[i];
        res[i] += C[i] * x[i+1];
    }
    if (is_need_print_vector)
        print_vector(res, n, "A*X");
    double norm = 0;
    for (int i = 0; i < n; i++){
        norm += pow(res[i] - b[i], 2);
    }
    for (int i = 0; i < n; i++){
        res[i] = b[i] - res[i];
    }
    if (is_need_print_vector)
        print_vector(res, n, "невязки");
    norm = sqrt(norm);
    printf("\nНорма вектора невзяки: ");
    cout << scientific << norm << endl;
    cout << "Норма вектора невзяки = " << norm << endl;
    delete [] res;
}

int main(){
    int N = 8;
    int const V = 4;
    cout << "N = " << N << "\n";


    // Матрица А
    // double* A = new double[N-1];
    // double* B = new double[N];
    // double* C = new double[N-1];
    double* A;
    double* B;
    double* C;
    make_arr(A, B, C, N, V);
    print_matrix(A, B, C, N);

    // Вектор в правой части "D"
    double* D;
    D = make_vector(N, V);
    print_vector(D, N, "D");

    // Решение, вектор X
    double* X_double = new double[N];
    X_double = solution_double(A, B, C, D, N);
    print_vector(X_double, N, "X_double");
    float* X_single;
    X_single = solution_float(A, B, C, D, N);
    print_vector(X_single, N, "X_single");

    norm_vector_nev(A, B, C, X_double, D, N, true);
    // for (int i = 0; i < N; i++)
    //     delete [] A[i];
    delete [] A;
    delete [] D;
    delete [] X_double;
    delete [] X_single;



    N = 3000000;
    cout << "\n\nN = " << N << "\n";
    make_arr(A, B, C, N, V);

    // print_matrix(A, N, "A");

    // Вектор в правой части "D"
    D = make_vector(N, V);
    // print_vector(D, N, "D");

    // Решение, вектор X
    X_double = solution_double(A, B, C, D, N);
    // print_vector(X_double, N, "X_double");
    X_single = solution_float(A, B, C, D, N);
    // print_vector(X_single, N, "X_single");

    norm_vector_nev(A, B, C, X_double, D, N, false);
    print_vector_range(X_double, 300001, 300005, "X_double");
    // for (int i = 0; i < N; i++)
    //     delete [] A[i];
    delete [] A;
    delete [] D;
    delete [] X_double;
    delete [] X_single;
    return 0;
}