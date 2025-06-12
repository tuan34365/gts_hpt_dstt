#include "bits/stdc++.h"
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output2.txt", "w", stdout);
    int n;
    cout << "Nhap so an (n): ";
    cin >> n;

    // Khai bao ma tran he so A, vector hang so b, vector nghiem x
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    vector<double> x(n, 0.0); // Nghiem ban dau bang 0
    vector<double> x_prev(n);
    double norm;
    int iteration = 0;

    // Nhap ma tran he so A
    cout << "Nhap ma tran he so A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> A[i][j];
        }
    }

    // Nhap vector hang so b
    cout << "Nhap vector hang so b (" << n << " phan tu):\n";
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    // Nhap nghiem ban dau (neu muon)
    cout << "Nhap nghiem ban dau x (" << n << " phan tu, mac dinh 0 neu bo qua):\n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = ";
        cin >> x[i];
    }

    cout.precision(10); // Do chinh xac cao

    // Phuong phap Gauss-Seidel
    do {
        // Luu nghiem truoc
        x_prev = x;

        // Tinh nghiem moi
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i]; // Cap nhat x[i]
        }

        // Tinh chuan 1
        norm = 0.0;
        for (int i = 0; i < n; i++) {
            norm += fabs(x[i] - x_prev[i]);
        }

        // In ket qua moi buoc lap
        cout << "Lan lap " << iteration << ": ";
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << x[i];
            if (i < n - 1) cout << ", ";
        }
        cout << ", norm = " << norm << endl;

        iteration++;

    } while (norm > 5e-5); // Dieu kien dung

    // In nghiem cuoi cung
    cout << "\nNghiem cuoi cung:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
    cout << "So lan lap: " << iteration << endl;

    // Kiem tra nghiem
    cout << "\nKiem tra nghiem:\n";
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        cout << "Phuong trinh " << i + 1 << ": " << sum << " = " << b[i] << endl;
    }

    return 0;
}
