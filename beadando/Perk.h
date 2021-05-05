#include <vector>
#include <utility>

class WQUni       // weighted quick union find
{
	
public:

	WQUni(int n)
	{
		flatgrid.reserve(n);  							

		for ( int i=0; i<=n; ++i )
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
	
public: 

    Percolation(int n); 
	
    bool checkOpen(int row, int col) const; 	 
    
    void open(int row, int col);   
              
    int openUnits();
    
    bool checkPerc();

private:
    
    int n;

    int n_units;

    WQUni wqu;   

    std::vector<bool> open_units;
        
    int n_open{0};       
       
    void checkValid(int row,int col) const;  

    void fuseTouchingUnits(int row,int col);
    
    int flattenRowCol(int row,int col) const;    
    
};

class PerkStats
{
	
    
public:
    
    PerkStats(int n);       

    double getpCrit();      

private:
    
    int n;  
    
    double p_crit;  

    double computeP_crit(Percolation& percolation);
    
    void computeProb();  
    
    
};


