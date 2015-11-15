//
// Created by eyefrog on 15/7/15.
//

#ifndef TINYRAY_MATRIX_H
#define TINYRAY_MATRIX_H

class Matrix {
public:
	double m[4][4];
public:
	Matrix(void);

	Matrix(const Matrix& mat);

	~Matrix();

	Matrix& operator=(const Matrix& rhs);

	Matrix& operator*(const Matrix& mat) const;

	Matrix& operator/(const double d);

	void set_identity(void);

};

#endif //TINYRAY_MATRIX_H
