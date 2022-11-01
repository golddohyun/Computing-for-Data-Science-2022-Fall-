#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

#pragma once

class Matrix {
private:
	int meth;
	int row;
	int col;
	double b0, b1;
	vector<vector<double>> data;


public :
	Matrix();
	Matrix(const vector<vector<double> > &m);
	Matrix operator+(const Matrix &other);
	Matrix operator-(const Matrix &other);
	Matrix operator*(const Matrix &other);
	Matrix Transpose();
	Matrix GetSubVectorbyColumn(int column);
	void Print();
	int GetNumRow();
	int GetNumColumn();
	double GetVal(int row, int col);
	friend Matrix SimpleLinearRegression(Matrix &X, Matrix &Y);

	friend Matrix Cor(Matrix &mat, int method=1) {
	Matrix t = mat.Transpose();
	Matrix corresult;
	vector < vector <double> > cor;
	double colsize = t.col;
	double rowsize = t.row;

	if (method==1) {
		vector < vector <double> > E;
		vector <double> sum_squared_E;

		for(int m=0; m < rowsize; m++){
			double mth_sum=0;
			double mth_mean;
			double MSE=0;
			vector <double> e;
			for (int n=0; n < colsize; n++) {
				mth_sum = mth_sum + t.data[m][n];
			}
			mth_mean = mth_sum / colsize;
			for (int k=0; k <colsize; k++){
				e.push_back(t.data[m][k]-mth_mean);
				MSE += pow(t.data[m][k]-mth_mean,2);

			}
			sum_squared_E.push_back(MSE);
			E.push_back(e);
		}

		for(int i=0; i< rowsize; i++){
			vector <double > v;
			for(int j=0; j<rowsize; j++){
				double s=0;
				for(int k=0; k<colsize; k++){
					s+= E[i][k]*E[j][k];
					}

				if (i==j) {v.push_back(1);}
				else {v.push_back(s/(sqrt(sum_squared_E[i])*sqrt(sum_squared_E[j])));}
			}
			cor.push_back(v);
		
		}
		corresult= Matrix(cor);
	}

	if (method == 2){
		vector < vector <double> > cortmp(rowsize, vector <double>(rowsize, 0));
		double denominator = colsize * (colsize - 1) / 2;

		for(int i=0; i< rowsize; i++){ 
			vector <double > v;
			
			for(int j=i; j< rowsize; j++){ 
				double numerator = 0;
				for(int k=0; k<colsize; k++){
				for (int l=0; l<k; l++){
					double left, right;
					left = (t.data[i][k] - t.data[i][l]);
					right = (t.data[j][k] - t.data[j][l]);
					if ( (left <= 0 && right <= 0) || (left >=0 && right >=0) ){
						numerator++;
					}
					else {numerator--;}

					}
					}
			double result = numerator / denominator;
			if (i==j) {cortmp[i][j] = 1;}
			else{
				cortmp[i][j] = result;
				cortmp[j][i] = result;
			}
			}
		}

		corresult = Matrix(cortmp);
	}
	return corresult;
};
	~Matrix();
};


class DataFrame {
public:
	vector<vector<double> > frame;
	int ReadData(string FileName, char sep, char comment, bool IsHeader);
	Matrix GetMatrix(int index[], int nColumn);
	DataFrame();
	~DataFrame();
};
