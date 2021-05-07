#include <vector>
#include <utility>
#include <random>
#include <math.h>
#include <algorithm> 


class WQUni
{
	
public:

	WQUni(int n)
	{
		flatgrid.reserve(n);  							

		for ( int i=0; i<=n; i++ )
		{                                
			flatgrid.push_back(i);  
		};
		
		size.assign(n,1);  
	}

	
	void join(int y, int x)  
	{
		int i = origin(y);  
		int j = origin(x);

		if (i == j) return; // ha közös felső elemhez tartoznak

		if ( size[i] < size[j] )   //  Q.union mellett  weighting
        { 
			flatgrid[i] = j;        // ha 'i'  fája kisebb 'j'-nél, azt egyenlővé teszi j-vel, igy alá kerül
			size[j] += size[i];   // és 'j' mérete nől  'i'-ével
		}

		else   // ha forditva, i>j méreténél, forditva adodnak össze a méretek ...
        {                 
			flatgrid[j] = i ;
			size[i] += size[j];
		}
	}

    bool connected(int y, int x) const   //  const 
	{
		return origin(y) == origin(x);  // origin(a legelső elem, ami fent van és ezek alatta vannak) 
									// ha egyezik a origin-juk, akkor kapcsolatban van a felső oldallal (nyílt path)
	}

private:
	std::vector<int> flatgrid,size;

	int origin(int i) const   //  mi az origin-je
	{
		while ( i != flatgrid[i] )  
			i = flatgrid[i];

		return i;
	}
};



class Percolation
{
	
	int n;

    int n_units;

    WQUni wqu;   

    std::vector<bool> open_units;
        
    int n_open{0};    
       
   	void fuseTouchingUnits(int row, int col)
	{
		int unit = flattenRowCol(row, col); // hanyadik elem

		if ( row != 1 && row != n && col != 1 && col != n ) { // ha nem a szélső kockákról van szó
		
			if ( checkOpen(row - 1, col) ) // megyünk az elemeken:ha az adott unit feletti kocka nyitva, joinolja össze a kettőt
				wqu.join(unit, flattenRowCol(row - 1, col)); // join adott unit a felettivel
		
			if ( checkOpen(row + 1, col) ) // ugyanez alatta, mellette...
				wqu.join(unit, flattenRowCol(row + 1, col)); 
		
			if ( checkOpen(row, col - 1) )
				wqu.join(unit, flattenRowCol(row, col - 1)); 

		
			if ( checkOpen(row, col + 1) )
				wqu.join(unit, flattenRowCol(row, col + 1)); 
		}

		// aztán jönnek a szélső kockák:

	
		else if (row == 1) 
		{		
			wqu.join(unit, 0); // a felső virtuális elemhez joinolta
		
			if ( checkOpen((int)2, col) ) 
				wqu.join(unit, flattenRowCol((int)2, col)); // alatta lévővel köti össze ha nyitva van

			if (col != 1)  // ha nem a bal szélső oszlop
			{ 
			
			if ( checkOpen(row, col - 1) ) // mellette balra lévő ha nyitva 
					wqu.join(unit, flattenRowCol(row, col - 1)); 
			}

			if (col != n) // ha nem a jobb szélső oszlop
			{ 			
				if ( checkOpen(row, col + 1) ) // mellette jobbra lévő ha nyitva 
					wqu.join(unit, flattenRowCol(row, col + 1)); 
			}
		}
	
		else if (row == n) 
		{		
			if ( checkOpen(row - 1, col) ) // az utolsó sorban lévő elemet felülről kapcsolja össze
				wqu.join(unit, flattenRowCol(row - 1, col)); 
		
			wqu.join(unit, n_units + 1); // legalsó virtuális sorhoz(elemhez) kapcsolja 

			if (col != 1) 
			{			
				if ( checkOpen(row, col - 1) )
					wqu.join(unit, flattenRowCol(row, col - 1)); 
			}

			if (col != n) 
			{			
				if ( checkOpen(row, col + 1) )
					wqu.join(unit, flattenRowCol(row, col + 1)); 
			}
		}

	
		else 
		{		
			if ( checkOpen(row - 1, col) )
				wqu.join(unit, flattenRowCol(row - 1, col)); 

		
			if ( checkOpen(row + 1, col) )
				wqu.join(unit, flattenRowCol(row + 1, col)); 

			if (col == n) 
			{			
				if ( checkOpen(row, col - 1) )
					wqu.join(unit, flattenRowCol(row, col - 1)); 
			}

			if (col == 1) 
			{			
				if ( checkOpen(row, col + 1) )
					wqu.join(unit, flattenRowCol(row, col + 1)); 
			}
		}
	}


public: 
    

	Percolation(int n):n(n), n_units(n * n), wqu(n_units + 2)
	                    // grid, összes unit,   N+2 az alső és felső virtuális lap miatt
											// wqu a 'flatgrid' vectort kesziti el az elemekkel +a fa méretét

	{	
		open_units.assign(n_units + 2, false); // az elején az ösaszes zarva van
		open_units[0] = true;     // első es utolso virtuális nyitva van
		open_units[n_units + 1] = true; 
	}
	  

	bool checkOpen(int row, int col) const 
	{	
		return open_units[flattenRowCol(row, col)]; 
	}	
    
     
	void open(int row, int col) // kinyit, ha még nem
	{	 

		if (!checkOpen(row, col)) { // nyitva?
			fuseTouchingUnits(row, col); // ha nem nyitva, fusion
											
			open_units[flattenRowCol(row, col)] = true; // melykek vannak nyitva
		
			n_open++; 	
		} 
	}           
   
	
	int openUnits() 
	{
		return n_open; 
	}
    
    bool checkPerc()
	{
		return wqu.connected(0, n_units + 1); // össze ér-e a -1ik és +1ik (virtuális sorok)										 
	}


	int flattenRowCol(int row, int col) const // row, col -ként megadott pozíció kilapítása 1D-be
	{															
		return 1 + (row - 1)*n + (col - 1); 
	}   
       
    
};

class PerkStats
{
	
    typedef std::pair<int, std::vector<int>> pair;
	
	int n;  
    
    pair p_crit;      

	pair computeP_crit(Percolation& percolation)
	{
 // random kinyitogatás
 
		std::random_device rd; 
		std::mt19937 eng(rd()); 							 
		std::uniform_int_distribution<> distr(1, n); 
	
		int OPENUNITS; // U : (abrazolas) flatgrid unitja
		int y, x; 		
		std::vector<int> gridU, gridX, gridY; 

	
		while ( !percolation.checkPerc() ) // addig amig enm perkolal, amig nem ér össze a virtualis sorokkal
		{ 
			y = distr(eng); // sor
			x = distr(eng); // oszlop
			percolation.open(y, x); // ezeknek a kinyitását végzi el a percolation-ön
			OPENUNITS = percolation.openUnits(); // mond meg a percolationről, h hany nyilt kocka van
			gridU.push_back(flattenRowColGrid(y, x)); // ide bekerültek olyanok is, amik mar kinyiltak 1x, de csak kis grideknel venni észre	
								
		}
	
		return pair((int)OPENUNITS, gridU); 
	}    
   

	void computeProb() // p* !
	{		
		Percolation percolation(n); 
		p_crit = computeP_crit(percolation); 		
	
	}	

	int flattenRowColGrid(int row, int col) const // PerkStats-nak is 
	{															
		return 1 + (row - 1)*n + (col - 1); 
	}
    
	int n_open{0}; 
	
public: 
   

	PerkStats(int n) : n(n) 				
	{	
		computeProb(); 
	}        

	int getpCrit() 
	{
		return p_crit.first; 
	} 

	bool checkOpenGrid(int row, int col) const //perkstats
	{	
		return open_units[flattenRowColGrid(row, col)]; 
	}		

	int openUnitsGrid() 
	{
		return n_open; 
	}       

	std::vector<int> getGrid() 

	{
		return p_crit.second; 
	}

	std::vector<bool> open_units;
	    
};


