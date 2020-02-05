#include "FullMatrix.h"

class FullData{

public:
//seção de membros públicos

	double ** data;
	//matriz de double com os dados

	FullData(Size size){
	//construtor de FullData

		data = (double**) calloc(size.m*sizeof(double*));
		//aloca memória para vetor de vetores de double, e inicializa com NULL

		for(int k = 0; k < size.m; k++){
		//para cada posição do vetor, alocar memória para outro vetor de double e inicializa com NULL

			*(data + k) = (double*) calloc(size.n*sizeof(double));
			//aloca memória para vetor de double e inicializa com NULL
		}
	}
};