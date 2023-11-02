
#include <iostream>
#include <cmath>


const int DIASTASH = 100;

struct Shmeio {
	float shm[DIASTASH];
};


float eukl_Apostash(Shmeio& a, Shmeio& b) {
	float apostash = 0.0;

	for (int i = 0; i < DIASTASH; i++) {
		apostash += (a.shm[i] - b.shm[i]) * (a.shm[i] - b.shm[i]);
	}
	return sqrt(apostash);
}