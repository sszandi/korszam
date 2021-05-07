#include "Perk.h"
#include <math.h>
#include <iostream>
#include <iomanip> 
#include <vector>

int main()
{
	int N, OU; // OU: open units
	std::vector<int> squares; 
	double p, NN; 
	std::vector<bool> squares2; 

	std::cout << "\nComputing percolation treshold of NxN grid\n"; 
	std::cout << "\nEnter N:\n"; 
 	std::cin >> N; 
	std::cout << "\n"; 
 
	{ 
	PerkStats computePerk(N); 
	squares=computePerk.getGrid(); 
	OU=computePerk.getpCrit(); 
	}


	NN=N*N; 
	p = OU/NN; 		

 	std::sort(squares.begin(), squares.end()); 
 	squares.erase(std::unique(squares.begin(), squares.end()), squares.end()); 
		
	squares2.assign(N*N, false); 

	for ( int i=0; i<OU; i++ ) 
			{        
				squares2[squares[i]-1] = true; 

			}; 

	if ( N<36 )	
	{

	for ( int i=1; i<N+1; i++ ) // sor
			{
				for ( int j=1; j<N+1; j++ ) // oszlop
				{
					if ( squares2[(1 + (i - 1)*N + (j - 1))-1]==1 )
					{
						std::cout<< " * "; 
																
					}

					else
					{
						std::cout<<"|||" ; 

					}			


				}
			std::cout << "\n"; 
			}
	}
	else std::cout << "Grid is not displayed if N>35 \n"; 


	std::cout << "\nThe critical p* is "<< '\t'<<std::setprecision(5) << p << '\n'; 
	std::cout << "Number of open units "<< '\t'<< OU; 
	std::cout << " \n" ; 
	std::cout << " \n" ; 

}
