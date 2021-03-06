/* file velocity_calc.c */
// c code for velocity_calc subroutines

#include <math.h>
#include "velocity_calc.h"

void velocity_calc(int nAtoms, int iter, int deltaWrite, double Ar_m, double Ar_m2d, double delta_t, double kB, double int_temp, double Tot_kinetic_en, double **atomVelocities, double **atomForces, double **old_atomForces) {
	
	int i, j;
	double component;
//	double sumv[3] = {0.0, 0.0, 0.0};
	double sumv2;
	double dof;

	dof = nAtoms*3;

	sumv2 = 0.0;

	for(i=0; i<nAtoms; i++) {
		for(j=0; j<3; j++) {
			component = 0.0;
			component = atomVelocities[i][j] + Ar_m2d*delta_t*(atomForces[i][j] + old_atomForces[i][j]);
			atomVelocities[i][j] = component;
			
			if(iter%deltaWrite==0) {
				sumv2 += atomVelocities[i][j]*atomVelocities[i][j];
			}
		}
	}
	
	Tot_kinetic_en = 0.5*Ar_m*sumv2;
	sumv2 = sumv2/dof;
	int_temp = (Ar_m*sumv2)/kB;

}	
