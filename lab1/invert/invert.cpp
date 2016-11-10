#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <array>

// DBL_EPSILON

const size_t MatrixDim = 3;

typedef std::array<std::array<double, MatrixDim>, MatrixDim> SquareMatrix;

//
//class Matrix
//{
//public:
//	Matrix(size_t dimension);
//	~Matrix();
//
//private:
//	size_t m_dim;
//	double **m_matrix;
//};
//
//Matrix::Matrix(size_t dimension)
//{
//	m_dim = dimension;
//	m_matrix = new (*double)[m_dim];
//}
//
//Matrix::~Matrix()
//{
//	delete[] m_matrix;
//}

int ReadFromStream(std::istream &inStream, SquareMatrix &matrix)
{
	for (size_t i = 0; i < MatrixDim; ++i)
		for (size_t j = 0; j < MatrixDim; ++j)
		{
			if (!(inStream >> matrix[i][j]))
			{
				std::cerr << "Error in read " << i * MatrixDim + j + 1 << "element" << std::endl;
				return 1;
			}
		}
	return 0;
}

int WriteToStream(std::ostream &outStream, SquareMatrix &matrix)
{
	for (size_t i = 0; i < MatrixDim; ++i)
	{
		for (size_t j = 0; j < MatrixDim; ++j)
		{
			outStream << std::fixed << std::setprecision(3) << matrix[i][j] << ' ';
		}
		outStream << std::endl;
	}
	return 0;
}

double getGaussCoefficient(SquareMatrix &matrix, size_t rowChange, size_t rowConst, size_t col)
{
	return matrix[rowChange][col] / matrix[rowConst][col];
}

void gaussMatrixTransformation(SquareMatrix &matrix, size_t rowChange, size_t rowConst, double coefficient)
{
	for (size_t col = 0; col < MatrixDim; ++col)
	{
		matrix[rowChange][col] = matrix[rowChange][col] - coefficient * matrix[rowConst][col];
	}
}

void setIdentity(SquareMatrix &matrix)
{
	for (size_t col = 0; col < MatrixDim; ++col)
		for (size_t row = 0; row < MatrixDim; ++row)
		{
			matrix[col][row] = (col == row) ? 1.0 : 0.0;
		}
}

bool tryMakeDiagonalElementNotZero(SquareMatrix &originalMatrix, SquareMatrix &invertedMatrix, size_t const col)
{
	size_t rowWtihMaxElement = col;
	for (size_t row = col + 1; row < MatrixDim; ++row)
	{
		if (abs(originalMatrix[rowWtihMaxElement][col]) < abs(originalMatrix[row][col]))
		{
			rowWtihMaxElement = row;
		}
	}
	if (rowWtihMaxElement == col)
	{
		return false;
	}
	else
	{
		std::swap(originalMatrix[col], originalMatrix[rowWtihMaxElement]);
		std::swap(invertedMatrix[col], invertedMatrix[rowWtihMaxElement]);
		return true;
	}
}

bool invertMatrix(SquareMatrix &originalMatrix, SquareMatrix &invertedMatrix)
{
	double transformCoefficient;
	setIdentity(invertedMatrix);
	for (size_t col = 0; col < MatrixDim; ++col)
	{
		// normalize if left top element is 0
		if (abs(originalMatrix[col][col]) < 2 * DBL_EPSILON)
		{
			if (tryMakeDiagonalElementNotZero(originalMatrix, invertedMatrix, col) == false)
			{
				std::cerr << "Matrix is singular" << std::endl;
				return false;
			}
		}
		for (size_t row = col + 1; row < MatrixDim; ++row)
		{
			// go down
			transformCoefficient = getGaussCoefficient(originalMatrix, row, col, col);
			gaussMatrixTransformation(originalMatrix, row, col, transformCoefficient);
			gaussMatrixTransformation(invertedMatrix, row, col, transformCoefficient);
		}
	}

	for (size_t col = MatrixDim - 1 ; col > 0; --col)
		for (size_t row = 0; row < col; ++row)
		{
			// go up
			transformCoefficient = getGaussCoefficient(originalMatrix, row, col, col);
			gaussMatrixTransformation(originalMatrix, row, col, transformCoefficient);
			gaussMatrixTransformation(invertedMatrix, row, col, transformCoefficient);
		}
	for (size_t col = 0; col < MatrixDim; ++col)
		for (size_t row = 0; row < MatrixDim; ++row)
		{
			invertedMatrix[row][col] = invertedMatrix[row][col] / originalMatrix[row][row];
		}
	return true;
}



bool invertMatrix(std::istream &inStream, std::ostream &outStream)
{
	SquareMatrix originalMatrix, invertedMatrix;
	ReadFromStream(inStream, originalMatrix);
	if (!invertMatrix(originalMatrix, invertedMatrix))
	{
		return false;
	};
	WriteToStream(outStream, invertedMatrix);
	return true;
}

int main(int argv, char *argc[])
{
	if (argv != 2)
	{
		std::cout << "Invalid arguments amount\n"
			<< "Usage invert.exe <file with matrix to invert>" << std::endl;
		return 1;
	}
	std::ifstream inFile(argc[1]);
	if (!inFile.is_open())
	{
		std::cout << "Can't open input file " << argc[1] << std::endl;
		return 2;
	}
	if (!invertMatrix(inFile, std::cout))
	{
		return 3;
	}

	return 0;
}

