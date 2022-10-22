#include <iostream>

using namespace std;

#include "matrix_exceptions.h"
#include "matrix.h"

int main()
{
    try
    {
        cout << "Testing constructors\n\n";

        Matrix<double> m1;
        cout << "Default:\n";
        cout << "matrix empty: " << m1.is_empty() << "\n";

        cout << "With sizes:\n";
        Matrix<double> m2(2, 3);
        cout << "matrix empty: " << m2.is_empty() << "\n";

        cout << "With elems:\n";
        Matrix<char> m3 = {{'A', 'a'}, {'B', 'b'}, {'E', 'e'}};
        cout << "m3:\n" << m3 << "\n";

        cout << "From existing matrix:\n";
        Matrix<char> m4(m3);
        cout << "m4:\n" << m4 << "\n";

        cout << "m3 == m4: " << (m3 == m4) << "\n";


        Matrix<int> m5 = Matrix<int>::identity_matrix(3, 3);
        Matrix<int> m6 = Matrix<int>::identity_matrix(3, 3);

        Matrix<int> sum = m5 + m6;
        cout << "\nSum of identity matrices\n";
        cout << sum;

        sum += 10;
        cout << "\n += 10\n";
        cout << sum << "\n";

        cout << "\nSub of identity matrices\n";
        Matrix<int> sub = m5 - m6;
        cout << sub;

        cout << "\n -= 6\n";
        sub -= 6;
        cout << sub;


        Matrix<int> m7 = {{1, 2, 3}};
        Matrix<int> m8 = {{4}, {5}, {6}};
        cout << "\nm7:\n" << m7;
        cout << "\nm8:\n" << m8;

        cout << "\nm7 == m8: " << (m7 == m8) << "\n";

        cout << "\nMult of matrices\n";
        cout << m7 * m8;

        cout << "\n Mult m7 with 2\n";
        cout << m7 * 2;

        cout << "\n Division m8 / 2\n";
        cout << m8 / 2;


        cout << "\nTranspose m7:\n";
        cout << m7.transpose();

        Matrix<int> m9 = {{2, 3}, {6, 8}};
        cout << "\nm9:\n" << m9;

        cout << "det = " << m9.det() << "\n";
        cout << "Inverted:\n";
        cout << m9.inverted();

        for (auto elem : m9)
            cout << elem << ' ';
    }
    catch (BaseException& err)
    {
        cout << err.what() << endl;
    }

    return 0;
}
