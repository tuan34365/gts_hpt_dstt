#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Hàm in vector
void printVector(const vector<double>& x, const string& label, int iteration) {
    cout << label << " (iteration " << iteration << "): [";
    for (size_t i = 0; i < x.size(); ++i) {
        cout << x[i];
        if (i < x.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Hàm tính chuẩn vô cực của vector (max norm)
double maxNorm(const vector<double>& v) {
    double maxVal = 0.0;
    for (double val : v) {
        if (abs(val) > maxVal) maxVal = abs(val);
    }
    return maxVal;
}

// Hàm tính AX - B
vector<double> computeResidual(const vector<vector<double>>& A, const vector<double>& X, const vector<double>& B) {
    vector<double> residual(B.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < A[i].size(); ++j) {
            sum += A[i][j] * X[j];
        }
        residual[i] = sum - B[i];
    }
    return residual;
}

// Phương pháp lặp đơn (Jacobi)
vector<double> jacobi(const vector<vector<double>>& A, const vector<double>& B, const vector<double>& X0, double epsilon, int& iterations) {
    vector<double> X = X0;
    vector<double> X_new(X0.size());
    int k = 0;
    double error = 0.0;
    do {
        for (size_t i = 0; i < A.size(); ++i) {
            double sum = B[i];
            for (size_t j = 0; j < A[i].size(); ++j) {
                if (j != i) sum -= A[i][j] * X[j];
            }
            X_new[i] = sum / A[i][i];
        }
        X = X_new;
        k++;
        printVector(X, "X (Jacobi)", k);
        vector<double> residual = computeResidual(A, X, B);
        error = maxNorm(residual);
    } while (error >= epsilon);
    iterations = k;
    return X;
}

// Phương pháp lặp Seidel (Gauss-Seidel)
vector<double> seidel(const vector<vector<double>>& A, const vector<double>& B, const vector<double>& X0, double epsilon, int& iterations) {
    vector<double> X = X0;
    int k = 0;
    double error = 0.0;
    do {
        for (size_t i = 0; i < A.size(); ++i) {
            double sum = B[i];
            for (size_t j = 0; j < A[i].size(); ++j) {
                if (j != i) sum -= A[i][j] * X[j];
            }
            X[i] = sum / A[i][i];
        }
        k++;
        printVector(X, "X (Seidel)", k);
        vector<double> residual = computeResidual(A, X, B);
        error = maxNorm(residual);
    } while (error >= epsilon);
    iterations = k;
    return X;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    int n;
    cout << "Nhap kich thuoc ma tran n: ";
    cin >> n;
    if (n <= 0) {
        cout << "Kich thuoc ma tran phai lon hon 0!" << endl;
        return 1;
    }

    // Nhập ma trận A
    vector<vector<double>> A(n, vector<double>(n));
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }

    // Nhập vector B
    vector<double> B(n);
    cout << "Nhap vector B (" << n << " phan tu):\n";
    for (int i = 0; i < n; ++i) {
        cout << "B[" << i << "]: ";
        cin >> B[i];
    }

    // Nhập vector khởi tạo X0
    vector<double> X0(n);
    cout << "Nhap vector khoi tao X0 (" << n << " phan tu):\n";
    for (int i = 0; i < n; ++i) {
        cout << "X0[" << i << "]: ";
        cin >> X0[i];
    }

    // Nhập sai số epsilon
    double epsilon;
    cout << "Nhap sai so epsilon: ";
    cin >> epsilon;
    if (epsilon <= 0) {
        cout << "Sai so epsilon phai lon hon 0!" << endl;
        return 1;
    }

    // Kiểm tra ma trận chiếm ưu thế đường chéo
    bool isDiagonallyDominant = true;
    for (int i = 0; i < n; ++i) {
        double diag = abs(A[i][i]);
        double sum = 0.0;
        for (int j = 0; j < n; ++j) {
            if (j != i) sum += abs(A[i][j]);
        }
        if (diag <= sum) {
            isDiagonallyDominant = false;
            break;
        }
    }
    if (!isDiagonallyDominant) {
        cout << "Canh bao: Ma tran khong chiem uu the duong cheo, phuong phap co the khong hoi tu!\n";
    }

    // Chạy phương pháp Jacobi
    cout << "\nPhuong phap lap don (Jacobi):\n";
    int jacobiIterations;
    vector<double> X_jacobi = jacobi(A, B, X0, epsilon, jacobiIterations);
    vector<double> residual_jacobi = computeResidual(A, X_jacobi, B);
    cout << "So lan lap (Jacobi): " << jacobiIterations << endl;
    cout << "Sai so (Jacobi, max norm of residual): " << maxNorm(residual_jacobi) << endl;

    // Chạy phương pháp Seidel
    cout << "\nPhuong phap lap Seidel (Gauss-Seidel):\n";
    int seidelIterations;
    vector<double> X_seidel = seidel(A, B, X0, epsilon, seidelIterations);
    vector<double> residual_seidel = computeResidual(A, X_seidel, B);
    cout << "So lan lap (Seidel): " << seidelIterations << endl;
    cout << "Sai so (Seidel, max norm of residual): " << maxNorm(residual_seidel) << endl;

    return 0;
}
