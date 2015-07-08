/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Takes as an input a list of points
 *    		    Outputs the fft
 *
 *        Version:  1.0
 *        Created:  07/08/2015 10:11:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathieu Tauban (MTn), mathieu.tauban@solvay.com
 *        Company:  LPMA (CNRS)
 *
 * =====================================================================================
 */

#include "fft.h"
#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <unistd.h>
#include <cmath>
#include <cstdlib>

void showhelp (char ** s) {
	std::cout << "mfft : gives as an input a column of data, returns the FFT\n" ; 
	std::cout << " option -r gives the folded transform for real data\n" ;	
   std::exit(EXIT_FAILURE);
}


int main(int argc, char** argv) {
    char tmp ; 
    bool rep = false ; 
    while((tmp=getopt(argc,argv,"hr"))!=-1)	{
	    switch (tmp) {
		case 'h':
			showhelp(argv) ; 
			break;
		case 'r':
			rep=true;
			break;
	    }
    }


	std::string line ; 

	std::vector<double> data ; 
	while(std::getline(std::cin,line )) {
		std::istringstream is (line) ; 
		double buffer ; 
		is >> buffer ; 
		data.push_back(buffer) ; 
	}
	std::clog << "Got\t" << data.size() << "\n" ; 
	unsigned int v = data.size() ; 
	v--;
	v |= v>>1 ;
	v |= v>>2 ; 
	v |= v>>4 ; 
	v |= v>>8; 
	v |= v>>16 ;
	v++; 
	std::clog << "Will perform a transform on\t" << v << "\n" ;
	
	
	complex *pSignal = new complex[v] ; 
	for (unsigned int i = 0 ; i < v ; i++) {
		if (i<data.size()) {
		pSignal[i] = complex(data[i],0.)  ; 
		} else {
		
		pSignal[i] = complex(0., 0.) ; 
		}
	}


	CFFT::Forward(pSignal, v) ; 
	unsigned int d = data.size() ; 

	if (!rep) {
 	for (unsigned int i = 0 ; i< v ; i++) {
	std::cout << pSignal[i].re()/d << "\t"  <<pSignal[i].im()/d <<   "\n" ;
	}
	}
	else {
		std::cout << pSignal[0].re()/d << "\t" << pSignal[0].im()/d << "\n" ;
	for (unsigned int i =1 ; i < (v+1)/2 ; i++) {
		
//	std::cout << std::pow ( std::pow( pSignal[i].re(),2.)  + std::pow( pSignal[v-i].re(), 2.) , .5 ) / d  << "\t"  << std::pow ( std::pow( pSignal[i].im(), 2.) + std::pow( pSignal[-i+v].im(), 2.),.5) / d<< "\n"  ; 
//
	std::cout <<  (pSignal[i].re()+ pSignal[v-i].re())  / d  << "\t"  << ( pSignal[i].im() - pSignal[-i+v].im() ) / d<< "\n"  ; 
	}
	}

return 0 ; 
}
