/* file force_energy_calc.c */
// c code for force_energy_calc subroutine

#include <math.h>                                                     
#include "force_energy_calc.h"

void force_energy_calc(int nAtoms, int iter, int deltaWrite, double box, double cutoff2, double Ar_eps, double Ar_sigma6, double Tot_potential_en, double **coord, double **atomForces, double **old_atomForces) {

	int atom1;
	int atom2;
	double dist2;
	double dist2d;
	double dist6d;
	double sigma_dist_6;
	int j;
	double component[3] = {0.0, 0.0, 0.0};
//	int atomCount;

	double ff;

	double sqrt(double x);

//	Tot_potential_en = 0.0;

	for(atom1=0; atom1<nAtoms-1; atom1++){
		for(atom2=atom1+1;atom2<nAtoms;atom2++) {
			dist2 = 0;
			dist2d = 0;
			dist6d = 0;
			for(j=0;j<3;j++) {
				component[j] = 0.0;
				component[j] = coord[atom1][j] - coord[atom2][j];
				if(component[j] < -box/2.0) {
					component[j] += box;
				} else if(component[j] > box/2.0) {
					component[j] -= box;
				}
				dist2 += component[j]*component[j]; 		// r^2 = x^2 + y^2 + z^2; 
			}
			if(dist2 < cutoff2) {
				dist2d = 1.0/dist2;
				dist6d = dist2d*dist2d*dist2d;
				sigma_dist_6 = Ar_sigma6*dist6d;
				ff = 48*Ar_eps*dist2d*sigma_dist_6*(sigma_dist_6-0.5);
				for(j=0; j<3; j++) {
					old_atomForces[atom1][j] = atomForces[atom1][j];
					old_atomForces[atom2][j] = atomForces[atom2][j];
					atomForces[atom1][j]+= ff*component[j]*sqrt(dist2);
					atomForces[atom2][j]+= -ff*component[j]*sqrt(dist2);
				}
				if(iter%deltaWrite==0) {
					Tot_potential_en += sigma_dist_6*(sigma_dist_6 - 1.0);
				}
			}
		}
	}
	
	if(iter%deltaWrite==0) {
		Tot_potential_en = 4.0*Ar_eps*Tot_potential_en;
	}

//	IDEA for increasing performance; move the 48*Ar_eps calculation outside of cutoff loop; I can't determine if this will actually be quicker though...
//	
//	for(atomCount=0; atomCount<nAtoms; atomCount++) {
//		for(i=0;i<3;i++) {
//			
//		}
//	}

}

