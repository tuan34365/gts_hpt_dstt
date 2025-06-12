#include <iostream>
#include <iomanip>
using namespace std;

// Hàm in ma trận
void inMaTran(double** a, double* b, int n, int buoc) {
    cout << "\nBuoc " << buoc << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(4) << a[i][j] << " ";
        }
        cout << "| " << setw(10) << b[i] << endl;
    }
    cout << endl;
}

// Hàm giải hệ phương trình bằng phương pháp Gauss
void giaiPhuongTrinhGauss(double** a, double* b, int n) {
    int buoc = 0;
    inMaTran(a, b, n, buoc); // In ma trận ban đầu

    // Giai đoạn khử (Elimination)
    for (int i = 0; i < n - 1; i++) {
        // Kiểm tra phần tử chéo khác 0
        if (a[i][i] == 0) {
            cout << "Phan tu tren duong cheo bang 0, khong the tiep tuc giai!" << endl;
            return;
        }

        for (int j = i + 1; j < n; j++) {
            double heSo = a[j][i] / a[i][i];

            // Cập nhật các phần tử trong hàng
            for (int k = i; k < n; k++) {
                a[j][k] -= heSo * a[i][k];
            }
            b[j] -= heSo * b[i];

            buoc++;
            inMaTran(a, b, n, buoc);
        }
    }

    // Giai đoạn thế ngược (Back substitution)
    double* x = new double[n];
    x[n-1] = b[n-1] / a[n-1][n-1];

    for (int i = n - 2; i >= 0; i--) {
        double tong = 0;
        for (int j = i + 1; j < n; j++) {
            tong += a[i][j] * x[j];
        }
        x[i] = (b[i] - tong) / a[i][i];
    }

    // In kết quả
    cout << "\nNghiem cua he phuong trinh:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << x[i] << endl;
    }

    delete[] x;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cout << "Nhap so luong phuong trinh (so an): ";
    cin >> n;

    // Cấp phát động ma trận
    double** a = new double*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }
    double* b = new double[n];

    // Nhập ma trận hệ số
    cout << "Nhap cac he so cua ma tran A:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }

    // Nhập vector vế phải
    cout << "Nhap cac gia tri ve phai b:\n";
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    // Giải hệ phương trình
    giaiPhuongTrinhGauss(a, b, n);

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    delete[] b;

    return 0;
}

/*
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100;

void printMatrix(double a[MAX][MAX], int n) {
    cout << "Ma tran hien tai:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(10) << fixed << setprecision(4) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------\n";
}

void gaussElimination(double a[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        // Tìm phần tử lớn nhất ở cột i để đổi hàng
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(a[k][i]) > fabs(a[maxRow][i]))
                maxRow = k;
        }

        // Đổi hàng
        for (int k = 0; k <= n; k++) {
            swap(a[maxRow][k], a[i][k]);
        }

        // Kiểm tra phần tử đường chéo có bằng 0 không
        if (fabs(a[i][i]) < 1e-8) {
            cout << "He phuong trinh vo nghiem hoac vo so nghiem.\n";
            return;
        }

        // Khử các hàng dưới
        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i] / a[i][i];
            for (int j = i; j <= n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }

        // In ma trận sau mỗi bước khử
        cout << "Sau lan lap thu " << i + 1 << ":\n";
        printMatrix(a, n);
    }

    // Giải bằng thế lùi
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }

    // In nghiệm
    cout << "Nghiem cua he:\n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << fixed << setprecision(6) << x[i] << endl;
    }
}

int main() {
    int n;
    double a[MAX][MAX];

    cout << "Nhap so an (n): ";
    cin >> n;

    cout << "Nhap ma tran he so (ma tran keo dai Ax = b):\n";
    for (int i = 0; i < n; i++) {
        cout << "Hang " << i + 1 << ": ";
        for (int j = 0; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    gaussElimination(a, n);

    return 0;
}
*/
/*
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Hàm kiểm tra sai số
bool checkTolerance(const vector<double>& x_new, const vector<double>& x_old, double tol) {
    for (size_t i = 0; i < x_new.size(); i++) {
        if (abs(x_new[i] - x_old[i]) > tol) {
            return false;
        }
    }
    return true;
}

// Hàm in vector
void printVector(const vector<double>& x, int iteration) {
    cout << "Lan lap " << iteration << ": [";
    for (size_t i = 0; i < x.size(); i++) {
        cout << fixed << setprecision(8) << x[i];
        if (i < x.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Phương pháp Gauss-Seidel
void gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0); // Nghiệm khởi đầu
    vector<double> x_old(n, 0.0); // Lưu nghiệm cũ
    int iteration = 0;

    cout << "Nghiem khoi dau: ";
    printVector(x, iteration);

    do {
        x_old = x; // Lưu nghiệm cũ
        iteration++;

        // Tính nghiệm mới theo Gauss-Seidel
        for (int i = 0; i < n; i++) {
            double sum1 = 0.0, sum2 = 0.0;
            // Tính tổng với các giá trị đã cập nhật (j < i)
            for (int j = 0; j < i; j++) {
                sum1 += A[i][j] * x[j];
            }
            // Tính tổng với các giá trị cũ (j > i)
            for (int j = i + 1; j < n; j++) {
                sum2 += A[i][j] * x_old[j];
            }
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
        }

        // In nghiệm sau mỗi lần lặp
        printVector(x, iteration);

    } while (!checkTolerance(x, x_old, tol) && iteration < maxIter);

    if (iteration >= maxIter) {
        cout << "Khong hoi tu sau " << maxIter << " lan lap!" << endl;
    } else {
        cout << "Nghiem hoi tu sau " << iteration << " lan lap." << endl;
    }
}

int main() {
    // Khởi tạo ma trận A + aI (a = 38) và vector b từ bài toán trước
    vector<vector<double>> A = {
        {48, 2, 1},
        {3, 53, 4},
        {1, 2, 50}
    };
    vector<double> b = {50, 60, 70};

    double tolerance = 1e-5; // Sai số 10^-5
    int maxIterations = 100; // Số lần lặp tối đa

    cout << "Giai he phuong trinh bang phuong phap Gauss-Seidel:" << endl;
    cout << "Ma tran A + aI:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(10) << A[i][j] << " ";
        }
        cout << "| " << b[i] << endl;
    }
    cout << endl;

    // Gọi hàm Gauss-Seidel
    gaussSeidel(A, b, tolerance, maxIterations);

    return 0;
}
*/
/*
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const int N = 3;
    const double EPS = 1e-5;
    double x[N] = {0, 0, 0};       // x1, x2, x3 ban đầu
    double prev_x[N];
    int iteration = 0;

    // Ma trận hệ số sau khi cộng aI
    double A[N][N] = {
        {42, -1,  0},
        {-1, 42, -1},
        { 0, -1, 41}
    };

    // Vector hằng số
    double b[N] = {1, 2, 3};

    cout << fixed << setprecision(6);

    while (true) {
        iteration++;
        for (int i = 0; i < N; i++) prev_x[i] = x[i];

        // Gauss-Seidel update
        x[0] = (b[0] + x[1]) / A[0][0];
        x[1] = (b[1] + x[0] + x[2]) / A[1][1];
        x[2] = (b[2] + x[1]) / A[2][2];

        // In kết quả lần lặp
        cout << "Iteration " << iteration << ": ";
        cout << "x1 = " << x[0] << ", ";
        cout << "x2 = " << x[1] << ", ";
        cout << "x3 = " << x[2] << endl;

        // Kiểm tra sai số tuyệt đối
        double max_diff = 0;
        for (int i = 0; i < N; i++) {
            double diff = fabs(x[i] - prev_x[i]);
            if (diff > max_diff)
                max_diff = diff;
        }

        if (max_diff < EPS)
            break;
    }

    cout << "\nNghiem gan dung sau " << iteration << " lan lap:\n";
    cout << "x1 = " << x[0] << "\n";
    cout << "x2 = " << x[1] << "\n";
    cout << "x3 = " << x[2] << "\n";

    return 0;
}
*/
