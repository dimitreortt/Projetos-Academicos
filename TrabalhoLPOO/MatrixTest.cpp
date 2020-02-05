#include "Matrix.h"

int main(){

try{
	FullMatrix * myMatrix = new FullMatrix(2, 2);
	FullMatrix * yourMatrix = new FullMatrix(2, 2);
	FullMatrix * matrix = 
	yourMatrix->data->data[0][0] = 2.0;
	yourMatrix->data->data[0][1] = 3;
	yourMatrix->data->data[1][0] = 10;
	yourMatrix->data->data[1][1] = 11;

	printf("%.2f %.2f %.2f %.2f\n", myMatrix->data->data[0][0], myMatrix->data->data[0][1], myMatrix->data->data[1][0], myMatrix->data->data[1][1]);
	myMatrix->add(*yourMatrix);
	printf("%.2f %.2f %.2f %.2f\n", myMatrix->data->data[0][0], myMatrix->data->data[0][1], myMatrix->data->data[1][0], myMatrix->data->data[1][1]);
	myMatrix->mul(1.5);
	printf("%.2f %.2f %.2f %.2f\n", myMatrix->data->data[0][0], myMatrix->data->data[0][1], myMatrix->data->data[1][0], myMatrix->data->data[1][1]);
}
catch (const MatrixException& e){
	puts(e.getMessage());
}
	puts("press any key to exit!");
	getchar();

	return 0;
}