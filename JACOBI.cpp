#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Hàm tính chuẩn Euclidean của hiệu hai vector
double euclidean_norm(const vector<double>& v1, const vector<double>& v2) {
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }
    return sqrt(sum);
}

// Hàm kiểm tra ma trận chéo trội hàng
bool is_diagonally_dominant(const vector<vector<double>>& A) {
    size_t n = A.size();
    for (size_t i = 0; i < n; ++i) {
        double diag = abs(A[i][i]);
        double sum_off_diag = 0.0;
        for (size_t j = 0; j < n; ++j) {
            if (j != i) {
                sum_off_diag += abs(A[i][j]);
            }
        }
        if (diag <= sum_off_diag) {
            cout << "Hang " << i + 1 << " khong cheo troi!" << endl;
            return false;
        }
    }
    return true;
}

// Hàm phương pháp Jacobi
void jacobi_method(const vector<vector<double>>& A, const vector<double>& b,
                   vector<double>& X, int k, vector<vector<double>>& history) {
    size_t n = A.size();
    vector<double> X_new(n);
    history.push_back(X); // Lưu X^(0)

    for (int iter = 0; iter < k; ++iter) {
        for (size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < n; ++j) {
                if (j != i) {
                    sum += A[i][j] * X[j];
                }
            }
            X_new[i] = (b[i] - sum) / A[i][i];
        }
        X = X_new;
        history.push_back(X); // Lưu nghiệm mỗi lần lặp
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    /// nhập A rồi đến B rồi đến X0
    int n; // Kích thước ma trận
    int k; // Số lần lặp
    cout << "Nhap kich thuoc ma tran n: ";
    cin >> n;
    cout << "Nhap so lan lap k: ";
    cin >> k;

    // Nhập ma trận A
    vector<vector<double>> A(n, vector<double>(n));
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A[i][j];
        }
    }

    // Nhập vector b
    vector<double> b(n);
    cout << "Nhap vector b (" << n << " phan tu):\n";
    for (int i = 0; i < n; ++i) {
        cout << "b[" << i + 1 << "] = ";
        cin >> b[i];
    }

    // Nhập vector xấp xỉ ban đầu X^(0)
    vector<double> X(n);
    cout << "Nhap vector xap xi ban dau X^(0) (" << n << " phan tu):\n";
    for (int i = 0; i < n; ++i) {
        cout << "X^(0)[" << i + 1 << "] = ";
        cin >> X[i];
    }

    // Kiểm tra ma trận chéo trội hàng
    if (!is_diagonally_dominant(A)) {
        cout << "Ma tran khong cheo troi hang, phuong phap Jacobi co the khong hoi tu!" << endl;
        return 1;
    }

    // Lưu lịch sử các lần lặp
    vector<vector<double>> history;

    // Chạy phương pháp Jacobi
    jacobi_method(A, b, X, k, history);

    // In nghiệm gần đúng X^(k)
    cout << "\nNghiem gan dung X^(" << k << "):\n";
    for (size_t i = 0; i < X.size(); ++i) {
        cout << fixed << setprecision(7);
        cout << "x_" << i + 1 << " = " << X[i] << endl;
    }

    // Tính và in sai số ||X^(k) - X^(k-1)||
    double error = euclidean_norm(history[k], history[k - 1]);
    cout << "\nSai so ||X^(" << k << ") - X^(" << k - 1 << ")|| = " << error << endl;

    // In lịch sử các lần lặp (tùy chọn)
    cout << "\nLich su cac lan lap:\n";
    for (size_t iter = 0; iter <= k; ++iter) {
        cout << "Lan lap " << iter << ": [ ";
        for (size_t i = 0; i < n; ++i) {
            cout << fixed << setprecision(7) << history[iter][i];
            if (i < n - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }

    return 0;
}
