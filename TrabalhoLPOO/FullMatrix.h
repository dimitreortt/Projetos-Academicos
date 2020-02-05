#ifndef __Matrix_h
#define __Matrix_h

#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

class MatrixException
{
public:
  MatrixException(const string& message):
    message { message }
  {
    // do nothing
  }

  const char* getMessage() const
  {
    return message.c_str();
  }

private:
  string message;

}; // MatrixException

class BadDimensionException: public MatrixException
{
public:
  BadDimensionException():
    MatrixException("Bad dimension")
  {
    // do nothing
  }

}; // BadDimensionException

class BadIndexException: public MatrixException
{
public:
  BadIndexException():
    MatrixException("Bad index")
  {
    // do nothing
  }

}; // BadIndexException

class DimensionsDoNotAgreeException: public MatrixException
{
public:
  DimensionsDoNotAgreeException():
    MatrixException("Dimensions do not agree"){
      // do nothing
    }
};

class Size
{
public: 	
    int m;
    int n;

	Size(int m, int n)
 	{
 		if (m <= 0 || n <= 0)
    		throw BadDimensionException();
		this->m = m;
		this->n = n;
	}
}; // Size

class FullData{

public:
//seção de membros públicos

	double ** data;
	//matriz de double com os dados

	FullData(Size * size){
	//construtor de FullData

		data = (double**) calloc(size->m,sizeof(double*));
		//aloca memória para vetor de vetores de double, e inicializa com NULL

		for(int k = 0; k < size->m; k++){
		//para cada posição do vetor, alocar memória para outro vetor de double e inicializa com NULL

			*(data + k) = (double*) calloc(size->n,sizeof(double));
			//aloca memória para vetor de double e inicializa com NULL
		}
	}
};

class FullMatrix{

public:
	FullData * data;
	Size * size;
public:
	
	FullMatrix(){
		data = nullptr;
		size = nullptr;
	}

	FullMatrix(int i, int j){
		size = new Size(i, j);
		data = new FullData(size);
	}

	FullMatrix add(FullMatrix f);

};



#endif // __FullMatrix_h
