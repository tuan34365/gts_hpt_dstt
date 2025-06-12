///GIẢI HPT AX = B
#include "bits/stdc++.h"
using namespace std;

// Hàm nhập ma trận A và vector B
void inputMatrix(vector<vector<float>>& A, int n) {
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "A[" << i+1 << "][" << j+1 << "] = ";
            cin >> A[i][j];
        }
    }
    cout << "\nNhap vector B (" << n << " phan tu):\n";
    for(int i = 0; i < n; i++) {
        cout << "B[" << i+1 << "] = ";
        cin >> A[i][n];
    }
}

// Hàm in ma trận
void printMatrix(const vector<vector<float>>& A, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            cout << setw(10) << fixed << setprecision(2) << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Hàm Gauss-Jordan
void gaussJordan(vector<vector<float>>& A, int n) {
    for(int i = 0; i < n; i++) {
        // Tìm phần tử chính (pivot)
        float pivot = A[i][i];
        if(pivot == 0) {
            cout << "Ma tran khong kha nghich!" << endl;
            return;
        }

        // Chia hàng i cho pivot để được 1 ở vị trí chính
        for(int j = 0; j <= n; j++) {
            A[i][j] = A[i][j] / pivot;
        }

        // Biến đổi các hàng khác để được 0 ở cột i
        for(int k = 0; k < n; k++) {
            if(k != i) {
                float factor = A[k][i];
                for(int j = 0; j <= n; j++) {
                    A[k][j] = A[k][j] - factor * A[i][j];
                }
            }
        }

        // In ma trận sau mỗi bước
        cout << "Buoc " << i + 1 << ":\n";
        printMatrix(A, n);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    // Nhập kích thước ma trận
    cout << "Nhap kich thuoc ma tran n: ";
    cin >> n;

    // Khởi tạo ma trận bổ sung [A|B] động
    vector<vector<float>> A(n, vector<float>(n + 1));

    // Nhập ma trận A và vector B
    inputMatrix(A, n);

    // In ma trận ban đầu
    cout << "\nMa tran ban dau:\n";
    printMatrix(A, n);

    // Áp dụng phương pháp Gauss-Jordan
    gaussJordan(A, n);

    // In nghiệm
    cout << "Nghiem cua he phuong trinh:\n";
    for(int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << A[i][n] << endl;
    }

    return 0;
}
