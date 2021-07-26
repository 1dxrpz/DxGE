#include <SFML/Graphics.hpp>
#include <vector>
#pragma once
using namespace ::std;

class DxEngineMath {
};


namespace dx {
    class Math {
    public:
        static float Q_rsqrt(float n)
        {
            long i;
            float x2, y;
            const float threehalfs = 1.5F;

            x2 = n * 0.5F;
            y = n;
            i = *(long*)&y;
            i = 0x5f3759df - (i >> 1);
            y = *(float*)&i;
            y = y * (threehalfs - (x2 * y * y));
            y = y * (threehalfs - (x2 * y * y));
            y = y * (threehalfs - (x2 * y * y));

            return y;
        }
        static float Sqrt(float n) {
            return 1 / Q_rsqrt(n);
        }
    };
    struct Size {
        int width = 1;
        int height = 1;
    };
    class Matrix {
    public:
        Size Size;
        Matrix(int n)
    {
        Size.height = 1;
        Size.width = n;
        values.push_back(vector<float>());
        for (int i = 0; i < n; i++) {
            values[0].push_back(0);
        }
    }
        Matrix(int n, int m)
    {
        Size.height = m;
        Size.width = n;
        for (int a = 0; a < m; a++) {
            values.push_back(vector<float>());
            for (int b = 0; b < n; b++) {
                values[a].push_back(0);
            }
        }
    }
        vector<vector<float>> GetValues()
    {
        return values;
    }
        Matrix operator+(Matrix m)
    {
        Matrix res(
            max(Size.width, m.Size.width),
            max(Size.height, m.Size.height));
        for (int a = 0; a < min(Size.width, m.Size.width); a++) {
            for (int b = 0; b < min(Size.width, m.Size.width); b++) {
                res.values[a][b] = values[a][b] + m.values[a][b];
            }
        }
        return res;
    }
        Matrix operator*(Matrix m)
    {
        Matrix res(m.Size.width, Size.height);
        for (int b = 0; b < res.Size.height; b++) {
            for (int a = 0; a < res.Size.width; a++) {
                float sample = 0;

                for (int i = 0; i < Size.width; i++) {
                    sample += values[b][i] * m.values[i][a];
                }

                res.values[b][a] = sample;
            }
        }
        return res;
    }
        vector<float>& operator[](const int a)
    {
        return values[a];
    }
        Matrix Transpose()
    {
        Matrix res(Size.height, Size.width);
        for (int y = 0; y < Size.height; y++) {
            for (int x = 0; x < Size.width; x++) {
                res.values[x][y] = values[y][x];
            }
        }
        return res;
    }
        static Matrix MatrixVector(sf::Vector3f v)
    {
        Matrix res(1, 4);
        res[0][0] = v.x;
        res[1][0] = v.y;
        res[2][0] = v.z;
        res[3][0] = 1;
        return res;
    }
    
    protected:
        vector<vector<float>> values;
    };
    class Vector : public Matrix {
    public:
        Vector(int n)
            : Matrix(n)
        {
        }
        float Length() {
            float res = 0;
            for (int i = 0; i < Size.width; i++) {
                res += values[0][i] * values[0][i];
            }
            return Math::Sqrt(res);
        }
    };
    class Vector2 : public Vector {
    public:
        Vector2()
            : Vector(2)
        {
        }
        Vector2(float x, float y)
            : Vector(2)
        {
            values[0][0] = x;
            values[0][1] = y;
        }
        float X() { return values[0][0]; }
        float Y() { return values[0][1]; }
        void X(float x) { values[0][0] = std::move(x); }
        void Y(float y) { values[0][1] = std::move(y); }
    
    private:
    };
    class Vector3 : public Vector {
    public:
        Vector3()
            : Vector(3)
        {
        }
        Vector3(float x, float y, float z) : Vector(3) {
            values[0][0] = x;
            values[0][1] = y;
            values[0][2] = z;
        }

        float X() { return values[0][0]; }
        float Y() { return values[0][1]; }
        float Z() { return values[0][2]; }
        void X(float x) { values[0][0] = std::move(x); }
        void Y(float y) { values[0][1] = std::move(y); }
        void Z(float z) { values[0][2] = std::move(z); }
    
    private:
    };
    class Point {
    public:
        int X;
        int Y;
        Point()
    {
        X = 0;
        Y = 0;
    }
        Point(int a, int b)
    {
        X = a;
        Y = b;
    }
        sf::Vector2f ToVector2()
    {
        return sf::Vector2f(X, Y);
    }
        Point operator+(Point p)
    {
        return Point(X + p.X, Y + p.Y);
    }
    };
}