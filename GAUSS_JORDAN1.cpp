/*
x1+x2-2x3+x4=1
x1-3x2+x3+x4=0
4x1-x2-x3-x4=1
4x1+3x2-4x3-x4=2

Nhap so phuong trinh (so an): 4
Nhap ma tran he so mo rong [A|B]:
Phuong trinh 1: 1 1 -2 1 1
Phuong trinh 2: 1 -3 1 1 0
Phuong trinh 3: 4 -1 -1 -1 1
Phuong trinh 4: 4 3 -4 -1 2
*/
#include "bits/stdc++.h"
using namespace std;

const double EPS = 1e-8;

int gaussJordan(vector<vector<double>>& a, vector<double>& res, vector<bool>& freeVar, int N) {
    int rank = 0;

    for (int col = 0, row = 0; col < N && row < N; col++) {
        int sel = row;
        for (int i = row; i < N; ++i)
            if (fabs(a[i][col]) > fabs(a[sel][col]))
                sel = i;

        if (fabs(a[sel][col]) < EPS)
            continue;

        swap(a[sel], a[row]);

        double pivot = a[row][col];
        for (int j = 0; j <= N; ++j)
            a[row][j] /= pivot;

        for (int i = 0; i < N; ++i) {
            if (i != row) {
                double factor = a[i][col];
                for (int j = 0; j <= N; ++j)
                    a[i][j] -= factor * a[row][j];
            }
        }

        row++;
        rank++;
    }

    // Kiểm tra vô nghiệm
    for (int i = 0; i < N; ++i) {
        bool allZero = true;
        for (int j = 0; j < N; ++j)
            if (fabs(a[i][j]) > EPS)
                allZero = false;
        if (allZero && fabs(a[i][N]) > EPS)
            return -1; // vô nghiệm
    }

    if (rank < N) {
        // Đánh dấu biến tự do
        vector<bool> pivotVar(N, false);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (fabs(a[i][j]) > EPS) {
                    pivotVar[j] = true;
                    break;
                }
            }
        }
        for (int i = 0; i < N; ++i)
            if (!pivotVar[i])
                freeVar[i] = true;

        return 0; // vô số nghiệm
    }

    for (int i = 0; i < N; ++i)
        res[i] = a[i][N];

    return 1; // duy nhất
}

int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    cout << "Nhap so phuong trinh (so an): ";
    cin >> N;

    vector<vector<double>> a(N, vector<double>(N + 1));
    vector<double> res(N, 0);
    vector<bool> freeVar(N, false);

    cout << "Nhap ma tran he so mo rong [A|B]:\n";
    for (int i = 0; i < N; ++i) {
        cout << "Phuong trinh " << i + 1 << ": ";
        for (int j = 0; j <= N; ++j)
            cin >> a[i][j];
    }

    int status = gaussJordan(a, res, freeVar, N);

    if (status == -1) {
        cout << "He phuong trinh vo nghiem.\n";
    } else if (status == 1) {
        cout << "He phuong trinh co nghiem duy nhat:\n";
        for (int i = 0; i < N; ++i)
            cout << "x" << i + 1 << " = " << fixed << setprecision(4) << res[i] << endl;
    } else {
        cout << "He phuong trinh co vo so nghiem.\nDang nghiem tong quat:\n";
        for (int i = 0; i < N; ++i) {
            if (freeVar[i]) {
                cout << "x" << i + 1 << " = t" << i + 1 << " (tu do)\n";
            } else {
                cout << "x" << i + 1 << " = ";
                double constant = a[i][N];
                bool printed = false;
                if (fabs(constant) > EPS) {
                    cout << fixed << setprecision(4) << constant;
                    printed = true;
                }

                for (int j = 0; j < N; ++j) {
                    if (freeVar[j] && fabs(a[i][j]) > EPS) {
                        if (printed)
                            cout << (a[i][j] > 0 ? " + " : " - ");
                        else if (a[i][j] < 0)
                            cout << "-";

                        cout << fixed << setprecision(4) << fabs(a[i][j]) << "*t" << j + 1;
                        printed = true;
                    }
                }

                if (!printed) cout << "0";
                cout << endl;
            }
        }
    }

    return 0;
}

