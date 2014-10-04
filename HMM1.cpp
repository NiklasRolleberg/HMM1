#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream> 

struct matrix 
{
	int row;
	int col;
	double** m;
	
	//constructor
	matrix(double** mat, int rows, int cols)
	{
		row = rows;
		col = cols;
		m = mat;
	}
	
	//constructor 2
	matrix(std::string in)
	{
		std::istringstream iss;
		iss.str(in);
		iss >> row >> col;
		
		m = (double**)calloc(row , sizeof(double *));
		for(int i=0 ; i< row ; ++i)
			m[i] = (double*)calloc(col , sizeof(double));
		
		for(int i=0;i<row;++i)
		{
			for(int j=0;j<col;++j)
			iss >> m[i][j];
		}
	}
	
	double get(int r, int c)
	{
		return m[r][c];
	}
	
	void print() 
	{
		for (int i=0;i<row;++i)
		{
			for(int j=0;j<col;++j)
				std::cout << m[i][j] <<" ";
			std::cout << std::endl;
		}		
	}
	
	void writeMatrix()
	{
		std::cout << row << " " << col;
		for(int i=0;i<row;++i) {
			for(int j=0; j<col;++j)
				std::cout << " " << m[i][j];
		}
	}
	
	matrix operator*(matrix H)
	{
		int newRows = row;
		int newCols = H.col;

		double** temp;
		temp = (double**)calloc(newRows , sizeof(double *));
		for(int i=0 ; i< newRows ; ++i)
			temp[i] = (double*)calloc(newCols , sizeof(double));
		
		//RÄKNA!
		double t;
		int i,j,k;
		for (i=0;i<newRows;++i)
		{
			for(j=0;j<newCols;++j)
			{
				t = 0;
				//row in first matrix X col in second matrix;
				for(k=0;k<col;++k)
					t+= (m[i][k] * H.get(k,j));
				temp[i][j] = t;
			}
		}
		return matrix(temp,newRows,newCols);
	}	
};

int main(int argc, char **argv)
{
	// Read the file	
	std::vector<std::string> board;
	for (std::string line; std::getline(std::cin, line);)
		board.push_back(line);
		
	matrix A = matrix(board[0]);
	matrix B = matrix(board[1]);
	matrix q = matrix(board[2]);
	
	matrix P = q*A;
	matrix Po = P*B;
	Po.writeMatrix();
	return 0;
}

