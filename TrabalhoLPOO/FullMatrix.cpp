#include "Matrix.h"

FullMatrix&
 FullMatrix::add(double s){
	for (int i = 0; i < this->size->m; i++){
		for(int j = 0; j < this->size->n; j++){
			this->data->data[i][j] += s;
		}
	}
}//

FullMatrix&
 FullMatrix::add(FullMatrix f){
	if(f.size->m != this->size->m || f.size->n != this->size->n)
		throw DimensionsDoNotAgreeException();

	for (int i = 0; i < this->size->m; i++){
		for(int j = 0; j < this->size->n; j++){
			this->data->data[i][j] += f.data->data[i][j];
		}
	}
}

FullMatrix&
 FullMatrix::sub(double s){
	for (int i = 0; i < this->size->m; i++){
		for(int j = 0; j < this->size->n; j++){
			this->data->data[i][j] -= s;
		}
	}
}

FullMatrix&
 FullMatrix::sub(FullMatrix f){
	if(f.size->m != this->size->m || f.size->n != this->size->n)
		throw DimensionsDoNotAgreeException();

	for (int i = 0; i < this->size->m; i++){
		for(int j = 0; j < this->size->n; j++){
			this->data->data[i][j] -= f.data->data[i][j];
		}
	}
}

FullMatrix&
 FullMatrix::mul(double s){
	for (int i = 0; i < this->size->m; i++){
		for(int j = 0; j < this->size->n; j++){
			this->data->data[i][j] *= s;
		}
	}
}

FullMatrix&
 FullMatrix::mul(FullMatrix f){
 	if(this->size->n != f.size->m)
 	/*se o número de linhas de this diverge do número de colunas de f,
 	lança exceção*/
 		throw DimensionsDoNotAgreeException();

 	FullMatrix multiply(this->size->n, f.size->m);
	/*cria nova matriz de tamanho this->n, f->m*/

 	double soma = 0;
	for(int i = 0; i < this->size->m; i++){
		for(int j = 0; j < f.size->n; j++){
			for(int k = 0; k < f.size->m; k++){
				soma += (this->data->data[i][k])*(f.data->data[k][j]);
			}
			/*o laço mais interno calcula a soma da linha em this com a
			coluna em f e armazena em soma*/
			multiply.data->data[i][j] = soma;
			/*cada posição da nova matriz recebe a soma correta*/
			soma = 0.0;
			/*reinicializa a soma*/
		}
	}

	return multiply;
}