#include "Perk.h"
#include <random>
#include <math.h>
#include <iostream>
#include <iomanip>  
#include <algorithm> 
#include <vector>

typedef std::pair<int, std::vector<int>> pair;
//typedef std::pair<double, int> pair;


Percolation::Percolation(int n) 	
	: n(n),          //  grid
	n_units(n * n),  // összes unit
	wqu(n_units + 2)   // N+2 az alső és felső virtuális lap miatt
						// wqu a 'flatgrid' vectort kesziti el az elemekkel  +a fa méretét

{	
	open_units.assign(n_units + 2, false); // az elején az ösaszes zarva van
	open_units[0] = true;                 // első es utolso virtuális nyitva van
	open_units[n_units + 1] = true;
}

void Percolation::open(int row,int col) // kinyit, ha még nem
{
	 

	if (!checkOpen(row,col)) {  // nyitva?
		fuseTouchingUnits(row,col);  // ha nem nyitva, fusion
											
		open_units[flattenRowCol(row,col)] = true;  // melykek vannak nyitva
		
		n_open++;  	
	}   
}

bool Percolation::checkOpen(int row, int col) const  
{
	
	return open_units[flattenRowCol(row,col)]; 
}		


bool PerkStats::checkOpen(int row, int col) const    //perkstats
{
	
	return open_units[flattenRowCol(row,col)]; 
}		

int Percolation::openUnits() 
{
	return n_open;
}

int PerkStats::openUnits() 
{
	return n_open;
}


bool Percolation::checkPerc()
{
	return wqu.connected(0,n_units + 1); // össze ér-e a -1ik és +1ik (virtuális sorok)
										  
}


int Percolation::flattenRowCol(int row,int col) const  // row, col -ként megadott pozíció kilapítása 1D-be
{															
	return 1 + (row - 1)*n + (col - 1);
}

int PerkStats::flattenRowCol(int row,int col) const  // PerkStats-nak is 
{															
	return 1 + (row - 1)*n + (col - 1);
}

void Percolation::fuseTouchingUnits(int row,int col)
{
	int unit = flattenRowCol(row, col);  // hanyadik elem

	if ( row != 1 && row != n && col != 1 && col != n ) {  // ha nem a szélső kockákról van szó
		
		if ( checkOpen(row - 1,col) ) // megyünk az elemeken:ha az adott unit feletti kocka nyitva,joinolja össze a kettőt
			wqu.join(unit, flattenRowCol(row - 1,col)); // join adott unit a felettivel
		
		if ( checkOpen(row + 1,col) )  // ugyanez alatta, mellette...
			wqu.join(unit, flattenRowCol(row + 1,col));
		
		if ( checkOpen(row,col - 1) )
			wqu.join(unit, flattenRowCol(row,col - 1));

		
		if ( checkOpen(row,col + 1) )
			wqu.join(unit, flattenRowCol(row,col + 1));
	}

	// aztán jönnek a szélső kockák:

	
	else if (row == 1) 
	{		
		wqu.join(unit, 0); // a felső virtuális elemhez joinolta
		
		if ( checkOpen((int)2,col) )  
			wqu.join(unit, flattenRowCol((int)2,col)); // alatta lévővel köti össze ha nyitva van

		if (col != 1) {  // ha nem a bal szélső oszlop
			
			if ( checkOpen(row,col - 1) )  // mellette balra lévő ha nyitva 
				wqu.join(unit, flattenRowCol(row,col - 1));
		}

		if (col != n)  // ha nem a jobb szélső oszlop
		{   			
			if ( checkOpen(row,col + 1) ) // mellette jobbra lévő ha nyitva 
				wqu.join(unit, flattenRowCol(row,col + 1)); 
		}
	}
	
	else if (row == n) 
	{		
		if ( checkOpen(row - 1,col) ) // az utolsó sorban lévő elemet felülről kapcsolja össze
			wqu.join(unit, flattenRowCol(row - 1,col));
		
		wqu.join(unit, n_units + 1); // legalsó virtuális sorhoz(elemhez) kapcsolja 

		if (col != 1) 
		{			
			if ( checkOpen(row, col - 1) )
				wqu.join(unit, flattenRowCol(row, col - 1));
		}

		if (col != n) 
		{			
			if ( checkOpen(row, col + 1) )
				wqu.join(unit, flattenRowCol(row,col + 1));
		}
	}

	
	else 
	{		
		if ( checkOpen(row - 1, col))
			wqu.join(unit, flattenRowCol(row - 1,col));

		
		if ( checkOpen(row + 1, col) )
			wqu.join(unit, flattenRowCol(row + 1,col));

		if (col == n) 
		{			
			if ( checkOpen(row,col - 1) )
				wqu.join(unit, flattenRowCol(row,col - 1));
		}

		if (col == 1) 
		{			
			if ( checkOpen(row, col + 1) )
				wqu.join(unit, flattenRowCol(row, col + 1));
		}
	}
}


PerkStats::PerkStats(int n)  
	: n(n) 				
{	
	computeProb();  
}							


void PerkStats::computeProb() //  p*  !
{		
		Percolation percolation(n);  
		p_crit = computeP_crit(percolation); 		
	
}

int PerkStats::getpCrit()   
{
	return p_crit.first;
}

std::vector<int> PerkStats::getGrid()   
//int PerkStats::getGrid()   

{
	return p_crit.second;
}

pair PerkStats::computeP_crit(Percolation& percolation)
{
    // random kinyitogatás
    
	std::random_device rd;   
	std::mt19937 eng(rd());  							 
	std::uniform_int_distribution<> distr(1, n);  
	
	int OPENUNITS;  // U : (abrazolas) flatgrid unitja
	int y, x;
	//double p;
	std::vector<int> gridU,gridX,gridY;
	

	
	while ( !percolation.checkPerc() ) // addig amig enm perkolal, amig nem ér össze a virtualis sorokkal
	{  
		y = distr(eng);  //  sor
		x = distr(eng);  //  oszlop
		percolation.open(y, x);  // ezeknek a kinyitását végzi el a percolation-ön
		OPENUNITS = percolation.openUnits(); //  mond meg a percolationről,h hany nyilt kocka van

		//gridU.reserve(open_units);

		
		gridU.push_back(flattenRowCol(y,x)); // ide bekerültek olyanok is,amik mar kinyiltak 1x,de csak kis grideknel venni észre	
		
						
	}


	
	
	return pair((int)OPENUNITS,gridU);  
}




//___________________________main____________________________________________________________

//  " p* = 0.592746 "

int main()
{
	int N,OU;  // OU: open units
	std::vector<int> squares;
	double p;
	std::vector<bool> squares2;

	std::cout << "\nComputing percolation treshold of NxN grid\n";
	std::cout << "\nEnter N:\n";
    std::cin >> N;   
	std::cout << "\n";
    
	{ 
	PerkStats computePerk(N);

	squares=computePerk.getGrid();
	OU=computePerk.getpCrit();	
		

    std::sort( squares.begin(), squares.end() );
    squares.erase( std::unique(squares.begin(), squares.end()), squares.end() );

		
	squares2.assign(N*N, false); 

for ( int i=0; i<OU; i++ )  
		{                                
			squares2[squares[i]-1] = true;   

		};

if ( N<36 )	
{

for ( int i=1; i<N+1; i++ )   // sor
		{
			for ( int j=1; j<N+1; j++ )  // oszlop
			{
				if ( squares2[(1 + (i - 1)*N + (j - 1))-1]==1 )
				{
					std::cout<< " * ";
					//std::cout << "\u2562";
										
				}

				else
				{
					std::cout<<"|||" ;

				}			


			}
		std::cout << "\n";
		}
}
else std::cout << "Grid is not displayed above N=35 \n";


p = static_cast<double>(OU)/(N*N);	
std::cout << "\nThe critical p* is " << '\t'<<std::setprecision(10) <<  p << '\n';
std::cout << "Number of open units " << '\t'  << OU << '\n\n';
//
}  

 

}
