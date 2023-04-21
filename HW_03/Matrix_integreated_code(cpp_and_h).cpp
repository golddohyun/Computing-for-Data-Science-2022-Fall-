#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

class Matrix {
private:
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
	void print();
	int GetNumRow();
	int GetNumColumn();
	double GetVal(int row, int col);
	friend Matrix SimpleLinearRegression(Matrix &X, Matrix &Y);
	friend Matrix Cor(Matrix &mat, int method = 1);
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

Matrix DataFrame::GetMatrix(int index[], int nColumn) {
	vector< vector<double> > temp;
	vector<double> numbers;
	Matrix matrix;

	for (auto & i : frame) {
		for (int j = 0; j < nColumn; j++) 
		{
			int idx = index[j];
			numbers.push_back(i[idx]);
		}
	temp.push_back(numbers);
	numbers.clear();
	}
	matrix = Matrix(temp);
	return Matrix{matrix};
};
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

void Matrix::print() {
	for (auto &i: data) {
		for (double &j: i) cout << j << " ";
	cout << endl;
	}
};

Matrix Matrix::operator+(const Matrix& other)
{
	vector< vector <double> > tot;
    for (int r=0;r<row;r++){
        vector <double> nums;
        for(int c=0;c<col;c++){
            nums.push_back(data[r][c]+other.data[r][c]);
        }
        tot.push_back(nums);
    }
    return Matrix(tot);
}


Matrix Matrix::operator-(const Matrix& other)
{
	vector< vector <double> > tot;
    for (int r=0;r<row;r++){
        vector <double> nums;
        for(int c=0;c<col;c++){
			nums.push_back(data[r][c] - other.data[r][c]);
        }
        tot.push_back(nums);
    }
    return Matrix(tot);
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

Matrix Cor(Matrix &mat, int method) {
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


int main() {
	DataFrame frame;
	frame.ReadData("coris.txt", ',', '#', true);

	int Column[3] = {1, 3, 4}; // sbp, ldl, adiposity
	Matrix m = frame.GetMatrix(Column, 3);

	Matrix m_t = m.Transpose();
	Matrix m_tm = m_t * m;

	cout << "Matrix M^T M:" << endl;
	m_tm.print();

	/////////////////////////////
	// Correlation Analysis (Pearson and Kendall)
	Matrix Pearson = Cor(m);
	Matrix Kendall = Cor(m, 2);

	cout << "Pearson:" << endl;
	Pearson.print();

	cout << "Kendall:" << endl;
	Kendall.print();

	Matrix a = Pearson + Kendall;
	Matrix b = Pearson - Kendall;
	cout << "Pearson + Kendall:" << endl;
	a.print();

	cout << "Pearson - Kendall:" << endl;
	b.print();

	/////////////////////////////
	// Simple Linear regression
	Matrix Y = m.GetSubVectorbyColumn(0); // sbp
	Matrix X = m.GetSubVectorbyColumn(1); // ldl

	Matrix Coeff = SimpleLinearRegression(X, Y);

	cout << "Simple Linear Regression Output:" << endl;
	Coeff.print(); 

	return 0;

}
