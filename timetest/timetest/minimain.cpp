#include"my_strtod.h"
#include<iostream>
using namespace std;

int main()

{

	char * str = "12345.6789";

	printf("%0.2f\n",my_strtod(str,0));

	printf("%f\n",my_atof(str));



	str = "-12345.6789";

	printf("%f\n",my_strtod(str,0));

	printf("%f\n",my_atof(str));


	char* endptr=NULL;
	str = "9.8546721E+4";
	

	printf("%f\n",my_strtod(str,& endptr));
	if(endptr)printf("error\n");

	printf("%f\n",my_atof(str));



	str = "-985467.21e-4";

	printf("%f\n",my_strtod(str,0));

	printf("%f\n",my_atof(str));



	system("pause");

	return 0;

}

