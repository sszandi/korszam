#include <vector>
#include <utility>
#include <random>
#include <math.h>
#include <algorithm> 


class WQUni   // a Weighted Quick Union Find műveletekhez tartozó osztály
{
	
public:

	WQUni(int N)
	{
		flatgrid.reserve(N);  		// egy sima vectorban fog tárolódni a grid összes eleme					

		for ( int i=0; i<=N; i++ )  
		{                                
			flatgrid.push_back(i);  // bele rak 0-N-ig számokat
		};
		
		size.assign(N,1);    // a wighted quick union-hoz használt méret
	}

	
	void join(int y, int x)    // 
	{
		int i = origin(y);  
		int j = origin(x);

		if (i == j) return; // ha közös felső elemhez tartoznak akkor visszatér (nem join-olja egybe őket)

		if ( size[i] < size[j] )   // ez a rész Q.union mellett a weighting 
        { 
			flatgrid[i] = j;       // ha 'i' origin alatt lévő fa kisebb 'j'-nél, azt egyenlővé teszi j-vel, igy alá kerül
			size[j] += size[i];    // és 'j' mérete nől  'i'-ével
		}

		else   // ha forditva, i>j méreténél, forditva adodnak össze a méretek ...
        {                 
			flatgrid[j] = i ;
			size[i] += size[j];
		}
	}

    bool connected(int y, int x) const   
	{
		return origin(y) == origin(x);  // origin(a legelső elem, ami fent van és ezek alatta vannak) 
									    // ha egyezik a origin-juk, akkor kapcsolatban van a felső oldallal (nyílt path)
	}

private:
	std::vector<int> flatgrid,size;

	int origin(int i) const   //  mi az origin-je az adott elemnek a grid-ben
	{
		while ( i != flatgrid[i] )   // megkeresi az orgin-jét a vectorban
			i = flatgrid[i];

		return i;
	}
};

class Percolation
{
	
	int N; 

    int n_units;

    WQUni wqu;  // a WQUnion-tól származik  

    std::vector<bool> open_units;
        
    int n_open{0};    
       
   	void fuseTouchingUnits(int y, int x)  // ha az adott elemmel erintkezők nyitva vannak, akkor join-olja őket
	{
		int unit = flatten(y, x);  // hányadik elemről van szó

		if ( y != 1 && y != N && x != 1 && x != N ) { // ha nem a szélső kockákról van szó
		
			if ( checkOpen(y - 1, x) ) // ha az adott elem feletti elem nyitva, joinolja össze a kettőt
				wqu.join(unit, flatten(y - 1, x)); 
		
			if ( checkOpen(y + 1, x) ) // ugyanez alatta, mellette...
				wqu.join(unit, flatten(y + 1, x)); 
		
			if ( checkOpen(y, x - 1) )
				wqu.join(unit, flatten(y, x - 1)); 

		
			if ( checkOpen(y, x + 1) )
				wqu.join(unit, flatten(y, x + 1)); 
		}

		// aztán jönnek a szélső kockák:

	
		else if (y == 1)  // ha az első sorban lévő elemről van szó
		{		
			wqu.join(unit, 0); // a felső virtuális elemhez joinolta
		
			if ( checkOpen((int)2, x) ) 
				wqu.join(unit, flatten((int)2, x)); // alatta lévővel köti össze ha nyitva van

			if (x != 1)  // ha nem a bal szélső oszlopban vagyunk
			{ 
			
			if ( checkOpen(y, x - 1) )  // mellette balra lévő ha nyitva, akkor vele összeköti
					wqu.join(unit, flatten(y, x - 1));   
			}

			if (x != N) // ha nem a jobb szélső oszlop
			{ 			
				if ( checkOpen(y, x + 1) ) // mellette jobbra lévő ha nyitva, akkor vele összeköti
					wqu.join(unit, flatten(y, x + 1)); 
			}
		}
	
		else if (y == N)  // ha az utolsó sorban vagyunk
		{		
			if ( checkOpen(y - 1, x) ) //  és ha nyitva, az adott elemet kapcsolja össze a felette lévővel
				wqu.join(unit, flatten(y - 1, x)); 
		
			wqu.join(unit, n_units + 1); // legalsó virtuális sorhoz(elemhez) kapcsolja 

			if (x != 1)  // ha nem a bal oszlopban van az adott elem
			{			
				if ( checkOpen(y, x - 1) ) // és ha nyitva 
					wqu.join(unit, flatten(y, x - 1));  // akkor a mellette balra lévővel kösse össze 
			}

			if (x != N)  // ha nem az utolsó oszlopban van az adott elem
			{			
				if ( checkOpen(y, x + 1) ) // és ha nyitva  
					wqu.join(unit, flatten(y, x + 1));  // akkor a mellette jobbra lévővel kösse össze 
			}
		}

	
		else  // maradék lehetőség az adott elem helyzetére
		{		
			if ( checkOpen(y - 1, x) )   // ha nyitva, a felette lévővel köti össze
				wqu.join(unit, flatten(y - 1, x)); 

		
			if ( checkOpen(y + 1, x) ) // ha nyitva, az alatta lévővel köti össze 
				wqu.join(unit, flatten(y + 1, x)); 

			if (x == N) 
			{			
				if ( checkOpen(y, x - 1) ) // ha nyitva, a mellette balra lévővel köti össze 
					wqu.join(unit, flatten(y, x - 1)); 
			}

			if (x == 1) 
			{			
				if ( checkOpen(y, x + 1) ) // ha nyitva, a mellette jobbra lévővel köti össze 
					wqu.join(unit, flatten(y, x + 1)); 
			}
		}
	}


public: 
    

	Percolation(int N):N(N), n_units(N * N), wqu(n_units + 2)
	                // elkészül a grid, N*N+2 az alső és felső virtuális lap miatt
					// wqu a 'flatgrid' vectort kesziti el az elemekkel +a fa méretét

	{	
		open_units.assign(n_units + 2, false); // False - az elején az összes elem zárva van
		open_units[0] = true;     // első és utolso virtuális elem viszont nyitva van
		open_units[n_units + 1] = true; 
	}
	  

	bool checkOpen(int y, int x) const   // megmondja, hogy az adott elem nyitva vagy sem
	{	
		return open_units[flatten(y, x)];  // az open_units adott indexű helyén true/false
	}	
    
     
	void open(int y, int x) // kinyit, ha még nincs nyitva
	{	 

		if (!checkOpen(y, x)) { 
			fuseTouchingUnits(y, x); // ha nincs nyitva, fusion
											
			open_units[flatten(y, x)] = true; // és átírja az állapotát nyitottra
		
			n_open++; 	// és a nyíltak számát eggyel növeli
		} 
	}           
   
	
	int openUnits() // a nyitott elemek számát kapjuk meg
	{
		return n_open; 
	}
    
    bool checkPerc()
	{
		return wqu.connected(0, n_units + 1); // perkolál ha össze ér-e a N*N+1-edik. és 0. (virtuális) sor.									 
	}


	int flatten(int y, int x) const // y, x -ként megadott pozíció kilapítása 1D-be
	{															
		return 1 + (y - 1)*N + (x - 1); 
	}   
       
    
};

class PerkStats  // a p* és a grid kirajzolásához szükséges dolgok
{
	
    typedef std::pair<int, std::vector<int>> pair;    //  (a computeP_crit 2 visszatérési ertekkel rendelkezik)
	
	int N;  
    
    pair p_crit;      

	pair computeP_crit(Percolation& percolation) 
	{
 		// random kinyitogatás 
		std::random_device rd; 
		std::mt19937 eng(rd()); 							 
		std::uniform_int_distribution<> distr(1, N); 
	
		int OPENUNITS; // a végső összes nyílt elem
		int y, x; 	   // a random koordináták/pozíciók a gridben
		std::vector<int> gridU;  // ebben a vectorban adja vissza a nyílt elemek helyét a kirajzoláshoz

	
		while ( !percolation.checkPerc() ) // addig amig nem perkolal (amíg nem ér össze a virtualis felső és alsó sorral)
		{ 
			y = distr(eng); // sor
			x = distr(eng); // oszlop
			percolation.open(y, x); // ezeknek a kinyitását végzi el 
			OPENUNITS = percolation.openUnits(); // hány nyilt elem van
			gridU.push_back(flattenyxGrid(y, x)); 	// bekerülnek a nyílt elemek helyei a kirajzoláshoz
								
		}
	
		return pair((int)OPENUNITS, gridU); 
	}    
   

	void computeProb() 
	{		
		Percolation percolation(N); 
		p_crit = computeP_crit(percolation); // p_crit -be belekerült az összes nyílt elem száma és a pozíciók a kirajzoláshoz	
	
	}	

	int flattenyxGrid(int y, int x) const 
	{															
		return 1 + (y - 1)*N + (x - 1); 
	}
    
	int n_open{0}; 
	
public: 
   

	PerkStats(int N) : N(N) 
	{	
		computeProb(); 
	}        

	int getpCrit() 
	{
		return p_crit.first; 
	} 

	bool checkOpenGrid(int y, int x) const 
	{	
		return open_units[flattenyxGrid(y, x)]; 
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


