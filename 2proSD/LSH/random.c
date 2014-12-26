#include "random.h"

/*Akeraios omoiomorfos se [start,end]*/
int getUniformInt(int rStart, int rEnd){
	int r;	
	r = rStart + (int)((rand() / (RAND_MAX + 1.0)) *(rEnd - rStart +1.0)); 
	return r;
}

/*Double omoiomorfos se [start,end]*/
double getUniformDouble(double rStart, double rEnd){
	double r;
	r = rStart + (rEnd-rStart)*((double)(rand())/((double)RAND_MAX));
	return r;
}

/*Double me ~N(0,1) me metasximatismo Marsaglia */
double getNormalDouble(){
	double y1,y2,x;
	double r = 0.0;
	do{	
	y1 = getUniformDouble(-1,1);
	y2 = getUniformDouble(-1,1);
	r = pow(y1,2) + pow(y2,2);
	} while (r>=1);
	x = (sqrt(-2*log(r)/r)) * y1;
	return x;	
}

/*Cauchy apo to piliko dio arithmon poy ~N(0,1) */
double getCauchyDouble(){
	double r;
	double x = getNormalDouble()*100;
	double y = getNormalDouble()*100;
	printf("x=%f and y=%f\n",x,y);
	if (abs(y) < 0.001){
    	y = 0.001;
    }
    r = x/y;
    return r;
  }


