#include "bits/stdc++.h"
using namespace std;

// Hàm in ma trận
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

// Hàm in vector
void printVector(const vector<double>& vec) {
    for (double val : vec) {
        cout << val << endl;
    }
}

// Hàm nhập ma trận A từ bàn phím
vector<vector<double>> inputMatrix(int n) {
    vector<vector<double>> matrix(n, vector<double>(n));
    cout << "Nhap ma tran A (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

// Hàm nhập vector B từ bàn phím
vector<double> inputVector(int n) {
    vector<double> vec(n);
    cout << "Nhap vector B (" << n << " phan tu):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "B[" << i << "] = ";
        cin >> vec[i];
    }
    return vec;
}

// Hàm phân tích Choleski: A = LL^T
bool choleskyDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            if (j == i) { // Phần tử đường chéo
                for (int k = 0; k < j; k++) {
                    sum += L[j][k] * L[j][k];
                }
                if (A[j][j] - sum < 0) {
                    cout << "Ma tran khong xac dinh duong." << endl;
                    return false;
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else { // Phần tử ngoài đường chéo
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                if (L[j][j] == 0) {
                    cout << "L[j][j] = 0, khong the phan tich." << endl;
                    return false;
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return true;
}

// Hàm giải hệ tam giác dưới: Ly = B
vector<double> solveLowerTriangular(const vector<vector<double>>& L, const vector<double>& B, int n) {
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        if (L[i][i] == 0) {
            cout << "L[i][i] = 0, khong the giai." << endl;
            return y;
        }
        y[i] = (B[i] - sum) / L[i][i];
    }
    return y;
}

// Hàm giải hệ tam giác trên: L^T x = y
vector<double> solveUpperTriangular(const vector<vector<double>>& L, const vector<double>& y, int n) {
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j]; // L^T là chuyển vị, nên dùng L[j][i]
        }
        if (L[i][i] == 0) {
            cout << "L[i][i] = 0, khong the giai." << endl;
            return x;
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
    return x;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cout << "Nhap kich thuoc ma tran (n): ";
    cin >> n;

    // Nhập ma trận A
    vector<vector<double>> A = inputMatrix(n);

    // Nhập vector B
    vector<double> B = inputVector(n);

    // Khởi tạo ma trận L
    vector<vector<double>> L(n, vector<double>(n, 0.0));

    // Phân tích Choleski
    cout << "Phan tich Choleski..." << endl;
    if (!choleskyDecomposition(A, L, n)) {
        cout << "Khong the phan tich Choleski." << endl;
        return 1;
    }

    // In ma trận A
    cout << "Ma tran A:" << endl;
    printMatrix(A);

    // In ma trận L
    cout << "Ma tran L:" << endl;
    printMatrix(L);

    // Giải hệ Ly = B
    cout << "Giai he Ly = B..." << endl;
    vector<double> y = solveLowerTriangular(L, B, n);
    cout << "Vector y:" << endl;
    printVector(y);

    // Giải hệ L^T x = y
    cout << "Giai he L^T x = y..." << endl;
    vector<double> x = solveUpperTriangular(L, y, n);
    cout << "Nghiem cua he phuong trinh (x):" << endl;
    printVector(x);

    return 0;
}
