//
// Created by eyesfrog on 2016-12-19.
//

#ifndef PBRT_TRANSFORM_H
#define PBRT_TRANSFORM_H

#include "pbrt.h"
#include "geometry.h"
#include <iostream>

struct Matrix4x4 {
    //Matrix4x4 Public Methods
    Matrix4x4()
    {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1]
                = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
    }

    Matrix4x4(Float mat[4][4]);

    Matrix4x4(Float t00, Float t01, Float t02, Float t03,
              Float t10, Float t11, Float t12, Float t13,
              Float t20, Float t21, Float t22, Float t23,
              Float t30, Float t31, Float t32, Float t33);

    friend Matrix4x4 Transpose(const Matrix4x4& mt);

    friend Matrix4x4 Inverse(const Matrix4x4&);

    static Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2)
    {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m1.m[i][0] * m2.m[0][j] +
                                 m1.m[i][1] * m2.m[1][j] +
                                 m1.m[i][2] * m2.m[2][j] +
                                 m1.m[i][3] * m2.m[3][j];
            }
        }

        return result;
    }

    bool operator==(const Matrix4x4& mt) const
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m[i][j] != mt.m[i][j])
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix4x4& mt) const
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (m[i][j] != mt.m[i][j])
                    return true;
            }
        }
        return false;
    }

    //Matrix4x4 Public Data
    Float m[4][4];
};

class Transform {
public:
    //Transform Public Methods
    Transform() { }

    Transform(const Float mat[4][4])
    {
        m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
                      mat[1][0], mat[1][1], mat[1][2], mat[1][3],
                      mat[2][0], mat[2][1], mat[2][2], mat[2][3],
                      mat[3][0], mat[3][1], mat[3][2], mat[3][3]);

        mInv = Inverse(m);
    }

    Transform(const Matrix4x4& m) : m(m), mInv(Inverse(m)) { }

    Transform(const Matrix4x4& m, const Matrix4x4& mInv) : m(m), mInv(mInv) { }

    friend Transform Inverse(const Transform& t)
    {
        return Transform(t.mInv, t.m);
    }

    friend Transform Transpose(const Transform& t)
    {
        return Transform(Transpose(t.m), Transpose(t.mInv));
    }

    Transform Translate(const Vector3f& delta);

    Transform Scale(Float x, Float y, Float z);

private:
    //Transform Private Data
    Matrix4x4 m, mInv;
};

#endif //PBRT_TRANSFORM_H
