#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "Matrix.h"

using namespace std;


DataFrame::DataFrame() {};

int DataFrame::ReadData(std::string FileName, char sep, char comment, bool IsHeader){
	string line;
	ifstream myfile(FileName);
	int header_cnt=0;

	if(myfile.is_open()){       
		while (getline(myfile,line)){
		if(line[0]==comment){continue;}
		else{     
			if (IsHeader==true){
				if(header_cnt==0){header_cnt+=1;}
				else{
					string temp;
					stringstream inputString(line);
					vector <double> numbers;
					while (getline(inputString, temp,sep)){
						numbers.push_back(stod(temp,0));
					}
					frame.push_back(numbers);
				}


			}
			else{
					string temp;
					stringstream inputString(line);
					vector <double> numbers;
					while (getline(inputString, temp,sep)){
						numbers.push_back(stod(temp,0));
					}
					frame.push_back(numbers);
			}
			}
		}
		}
		myfile.close();
		
	return 0;}
DataFrame::~DataFrame() {};


Matrix::Matrix() {};
Matrix::Matrix(const vector<vector<double>> &m) {
	data = m;
	col = m[0].size();
	row = m.size();
}

int Matrix::GetNumRow() {
	return row;
}

int Matrix::GetNumColumn() {
	return col;
}


void Matrix::Print() {
	for (auto &i: data) {
		for (double &j: i) cout << j << " ";
	cout << endl;
	}
};


Matrix Matrix::operator+(const Matrix& other)
{
	vector<vector<double>> result(row, vector<double>(col, 0));
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		result[i][j] = data[i][j] + other.data[i][j];
	
	return Matrix(result);
}


Matrix Matrix::operator-(const Matrix& other)
{
	vector<vector<double>> result(row, vector<double>(col, 0));
	for (int i = 0; i < row; i++)
	for (int j = 0; j < col; j++)
	result[i][j] = data[i][j] - other.data[i][j];

	return Matrix(result);
}


Matrix Matrix::operator*(const Matrix &other) {
	// Set matrix size to be generated as a result, initialize to zero
	vector<vector<double>> result(row, vector<double>( other.col, 0));

	// Print error message if multiplication is not possible
	if(col != other.row){ throw invalid_argument("Dot Product Unavailable"); }

	for (int i = 0; i < row ; i++) {
		for (int j = 0; j < other.col ; j++) {
			double sum = 0;
			for (int k = 0; k < other.row ; k++) {
				sum += data[i][k] * other.data[k][j];
			}
			result[i][j] = sum;
		}
	}
	return Matrix{result};
}


Matrix Matrix::GetSubVectorbyColumn(int column) {
	vector <vector<double>> subvec(row, vector<double>(0));
	for (int i = 0; i < row; i++){
		subvec[i].push_back(data[i][column]);
	}
	return Matrix{subvec};
};

Matrix Matrix::Transpose(){
	vector<vector<double> > trans_vec(col, vector<double>());
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			trans_vec[j].push_back(data[i][j]);}
	}
	return Matrix{trans_vec};
};


Matrix::~Matrix() {}

Matrix SimpleLinearRegression(Matrix &X, Matrix &Y){
	if (X.GetNumRow() != Y.GetNumRow()) {cout << "Data length mismatch" << endl;}
	vector <vector<double>> coeffs(2, vector<double>(0));
	double sumX=0, sumX2=0, sumY=0, sumXY=0;
	double b0, b1;
	double cnt = X.GetNumRow();

	for (auto &xi: X.data) {
		for (double &xj: xi) {
			sumX = sumX + xj;
			sumX2 = sumX2 + xj*xj;}
	}
	for (auto &yi: Y.data) {
		for (double &yj : yi) {
			sumY = sumY + yj;}
	}
	for (int i = 0; i < cnt; i++){
		sumXY = sumXY + X.data[i][0] * Y.data[i][0];}

	b1 = (cnt*sumXY-sumX*sumY)/(cnt*sumX2-sumX*sumX);
	b0 = (sumY - b1*sumX)/cnt;

	coeffs[0].push_back(b0);
	coeffs[1].push_back(b1);
	
	return Matrix{coeffs};
};
