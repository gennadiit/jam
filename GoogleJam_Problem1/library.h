//////////////////////////////////////////////////////////////////////////

#include <vector>
#include <math.h>
using namespace std;

/*
* Ordered directions including diagonal moves
*/
//int dirx[]={1, 1, 0, -1, -1, -1,  0, 1};
//int diry[]={0, 1, 1,  1,  0, -1, -1, -1};

/*
struct MYNODE {
};

bool operator<(const MYNODE& n1, const MYNODE& n2)
{
}

*/
/**
* CmpFraction compare fractions a1/b1 and a2/b2
*/

int CmpFraction(int a1, int b1, int a2, int b2)
{
	long long c=a1*(long long)b2-a2*(long long)b1;
	long long d=b1*(long long)b2;

    if(c==0)
		return 0;

	long long k=c^d;
	if(k&0x8000000000000000LL)
		return -1;
	else
		return 1;
}

/**
* CeilInt computes smallest int k so n*a/b <= k
*/
long long CeilInt(long long n, long long a, long long b)
{
	long long k=(long long)((((double)n)/b)*a);

	long long na=n*a;
	long long kb=k*b;

	if(na<=kb)
	{
		if(na>(kb-b))
			return k;
		else
			return k-1;
	}
	else
		return k+1;
}

/**
* FloorInt computes greatest int k so n*a/b >= k
*/
long long FloorInt(long long n, long long a, long long b)
{
	long long k=(long long)((((double)n)/b)*a);

	long long na=n*a;
	long long kb=k*b;

	if(na>=kb)
	{
		if(na<(kb+b))
			return k;
		else
			return k+1;
	}
	else
		return k-1;
}


/** class for calculating hash value of long long variable
*/
class HashCompLongLong {
public:
	enum
	{	// parameters for hash table
		bucket_size = 4,	// 0 < bucket_size
		min_buckets = 8};	// min_buckets = 2 ^^ N, 0 < N

		bool operator()(long long l1, long long l2) const
		{
			return l1<l2;
		}

		size_t operator () (long long l) const
		{
			return static_cast<size_t>(l%((1ll<<31)-1));
		}
};

//typedef hash_map<long long, int, HashCompLongLong> MyHash;

struct HashCompString {
	enum
	{	// parameters for hash table
		bucket_size = 4,	// 0 < bucket_size
		min_buckets = 8 };	// min_buckets = 2 ^^ N, 0 < N

	bool operator()(const string& s1, const string& s2) const
	{
		return s1<s2;
	}

	size_t operator()(const std::string& Key) const
	{
		size_t hash = 5381;
		for (std::string::const_iterator c = Key.begin(), end = Key.end(); c != end; ++c)
			hash = ((hash << 5) + hash) + (*c); /* hash * 33 + c */

		return hash;
	}
};

//typedef hash_map<string, int, HashCompString> MyHash;


//////////////////////////////////////////////////////////////////////////
/**
* @name GetNumSums calculates number ways we can represent number as sum of numcompositors compositors
  TODO: Verify implementation
*/
/*
long long GetNumSums(int number, int numcompositors, vector<vector<long long>>& m)
{
	long long l;
	if((l=m[numelements][numparts])>=0)
		return l;

	l=GetNumPartitions(numelements-1, numparts-1, m) + numparts*GetNumPartitions(numelements-1, numparts);
}

long long InitPartitionsMatrix(int numelements, vector<vector<long long>>& m)
{
	m.resize(numelements+1);

	for(int i=0; i<=numelements; ++i)
	{
		m[i].resize(numelements+1);
		m[i][0]=0;

		for(int j=1; j<i; ++j)
			m[i][j]=-1;
		m[i][i]=1;
		for(int j=i+1; j<=numelements; ++j)
			m[i][j]=0;
	}

}
*/

//////////////////////////////////////////////////////////////////////////
/**
* @name GetNumPartitions calculates number ways we can numelements distinguishable items part into 
*	numparts indistinguishable parts.
*/
/*
long long GetNumPartitions(int numelements, int numparts, vector<vector<long long>>& m)
{
	long long l;
    if((l=m[numelements][numparts])>=0)
		return l;

	l=GetNumPartitions(numelements-1, numparts-1, m) + numparts*GetNumPartitions(numelements-1, numparts);
}

long long InitPartitionsMatrix(int numelements, vector<vector<long long>>& m)
{
	m.resize(numelements+1);

	for(int i=0; i<=numelements; ++i)
	{
		m[i].resize(numelements+1);
		m[i][0]=0;
		
		for(int j=1; j<i; ++j)
			m[i][j]=-1;
		m[i][i]=1;
		for(int j=i+1; j<=numelements; ++j)
			m[i][j]=0;
	}

}
*/

//////////////////////////////////////////////////////////////////////////

/// Environment for using arrays of properties (not arrays of elements with properties)
// with STL algorithms

/// Sample
// MAKESEQ(vn, countries);
// sort(vn.begin(), vn.end(), LessFun(&countries, &names, &names));

#define MAKESEQ(vname, vtempl) vector<int> vname; FillVector(vname, vtempl.size());

template<class T>
void FillVector(T& v, int num)
{
	v.resize(num);
	int c=0;
	for(int i=0; i<num; ++i)
	{
		v[i]=c++;
	}
}

int PredConst=0;

template<class T1, class T2=int, class T3=int>
class LessPred {
public:
	LessPred(T1 * pv1, T2 * pv2, T3 * pv3) : v1(*pv1), v2(*pv2), v3(*pv3) {}
	bool operator() (int i, int j)
	{
		return v1[i] < v1[j];
	}

	T1& v1;
	T2& v2;
	T3& v3;
};

template<class T1, class T2, class T3>
LessPred<T1, T2, T3> LessFun(T1 * pv1, T2 * pv2=&PredConst, T3 * pv3=&PredConst)
{
	return LessPred<T1, T2, T3>(pv1, pv2, pv3);
}

//////////////////////////////////////////////////////////////////////////
/**
* @name GetFullName calculates anticlockwise angle relatively (1, 0) --> vector
*/
double GetFullAngle(double x, double y)
{
	double s=y/sqrt(x*x+y*y);
	double a=asin(s);
	if(x>=0)
	{
		if(y<0)
			a=2*M_PI+a;
	}
	else
		a=M_PI-a;

	return a;
}

/**
* @name GetFullName calculates anticlockwise coef relatively (1, 0) --> vector
*/
double GetFullAngleCoef(double x, double y)
{
	double a=y/sqrt(x*x+y*y);
	if(x>=0)
	{
		if(y<0)
			a=4+a;
	}
	else
		a=2-a;

	return a;
}

//////////////////////////////////////////////////////////////////////////

/**
* @name PolygonAreaSigned calculates signed area of the polygon with n vertices (the last vertex is NOT equal the first one)
*/
template<class T>
double PolygonAreaSigned(T& vx, T& vy, int n)
{
	double a=0;
	int i;
	int n1=n-1;

	for (i=1; i<n1; i++) 
	{
		a += vx[i] * (vy[i+1] - vy[i-1]);
	}
	a += vx[i] * (vy[0] - vy[i-1]);

	a/=2;

	return a;
}

/**
* @name PolygonArea calculates area of the polygon with n vertices (the last vertex is NOT equal the first one).
*  Area is negative if the polygon is oriented clockwise
*/
template<class T>
double PolygonArea(T& vx, T& vy, int n)
{
	return fabs(PolygonAreaSigned(vx, vy, n));
}

//////////////////////////////////////////////////////////////////////////

/*
//format "h:mPM"
int GetTimeInMinutes(const string& str, int * ppos=NULL)
{
	int h=0, m=0, ret;
	regex_t reg;
	string pattern="[:blank:]*([0-9]*):([0-9]*)(pm|am|())";
	regmatch_t matches[10];

	int r=regcomp(&reg, pattern.c_str(), REG_EXTENDED|REG_ICASE);

	if(regexec(&reg, str.c_str(), 10, matches, 0)==0)
	{
		if(ppos)
			*ppos=(int)matches[0].rm_eo;

		if(matches[1].rm_so>=0)
			h=atoi(str.substr(matches[1].rm_so, matches[1].rm_eo-matches[1].rm_so).c_str());
		if(matches[2].rm_so>=0)
			m=atoi(str.substr(matches[2].rm_so, matches[2].rm_eo-matches[2].rm_so).c_str());
		if(matches[3].rm_so>=0)
		{
			char c=str[matches[3].rm_so];
			if((c=='P') || (c=='p'))
			{
				if(h!=12)
					h+=12;
			}
			else if((c=='A') || (c=='a'))
			{
				if(h==12)
					h=0;
			}
		}
		ret=h*60+m;
	}
	else
	{
		ret=-1;
		if(ppos)
			*ppos=0;
	}

	regfree(&reg);

	return ret;
}

//format "[h:]m:sPM"
int GetTimeInSeconds(const string& str, int * ppos=NULL)
{
	int h=0, m=0, s=0, ret;
	regex_t reg;
	string pattern="[:blank:]*(([0-9]*):|())([0-9]*):([0-9]*)(pm|am|())";
	regmatch_t matches[10];

	int r=regcomp(&reg, pattern.c_str(), REG_EXTENDED|REG_ICASE);

	if(regexec(&reg, str.c_str(), 10, matches, 0)==0)
	{
		if(ppos)
			*ppos=(int)matches[0].rm_eo;

		if(matches[2].rm_so>=0)
			h=atoi(str.substr(matches[2].rm_so, matches[2].rm_eo-matches[2].rm_so).c_str());
		if(matches[4].rm_so>=0)
			m=atoi(str.substr(matches[4].rm_so, matches[4].rm_eo-matches[4].rm_so).c_str());
		if(matches[5].rm_so>=0)
			s=atoi(str.substr(matches[5].rm_so, matches[5].rm_eo-matches[5].rm_so).c_str());
		if(matches[6].rm_so>=0)
		{
			char c=str[matches[6].rm_so];
			if((c=='P') || (c=='p'))
			{
				if((h!=12) && (h!=0))
					h+=12;
			}
			else if((c=='A') || (c=='a'))
			{
				if(h==12)
					h=0;
			}
		}
		ret=h*3600+m*60+s;
	}
	else
	{
		ret=-1;
		if(ppos)
			*ppos=0;
	}

	regfree(&reg);

	return ret;
}
*/

bool IsPrime(int c)
{
	if(c<=1)
		return false;

	if((c%2)==0)
		return (c==2);
	
	int ub=(int)sqrt((double)c);
	int i;
	for(i=3; i<=ub; i+=2)
	{
		if((c%i)==0)
			return false;
	}
    
	return true;
}

void GetPrimes(int upperBound, vector<int>& res)
{
	if(upperBound<=1)
		return;

	res.push_back(2);

	int ub=upperBound;
	int n;
	int i, k;

	for(i=3; i<=ub; i+=2)
	{
		n=(int)res.size();
		for(k=1; k<n; ++k)
		{
			if((i%res[k])==0)
				break;
		}

		if(k==n)
			res.push_back(i);
	}
}

//Find the greatest common divisor of p and q, and p*x+q*y = Gcd(p, q) 
int Gcd(int p, int q, int * px=NULL, int * py=NULL)
{
	if(p<q)
		return Gcd(q, p, py, px);

	if(q==0)
	{
		if(px)
			*px=1;
		if(py)
			*py=0;

		return p;
	}

	int x1, y1;
	int g=Gcd(q, p%q, &x1, &y1);

	if(px)
		*px=y1;
	if(py)
		*py=(int)(x1-floor((double)(p/q))*y1);

	return g;		
}

/*
 * Calculates next ball position and direction after the reflection from the wall in a rectangle box, 
 * if it has currently (curx, cury) position,
 * direction dir (0 - right up, 1 - right down, 2 - left down, 3 - left up).
 * Touching angle is equal to the reflection angle.
 * If ball goes into the conner it is reflected in opposite direction.
 */
void NextBallPos(int& curx, int& cury, int& dir, int rows, int columns)
{
	int dx=columns-curx-1;
	int dy=rows-cury-1;

	switch(dir)
	{
	case 0:
		if(dy<dx)
		{
			curx+=dy+1;
			cury+=dy;
			dir=1;
		}
		else if(dy>dx)
		{
			curx+=dx;
			cury+=dx+1;
			dir=3;
		}
		else
		{
			curx+=dx;
			cury+=dx;
			dir=2;
		}
		break;

	case 1:
		if(cury<dx)
		{
			curx+=cury+1;
			cury-=cury;
			dir=0;
		}
		else if(cury>dx)
		{
			curx+=dx;
			cury-=dx+1;
			dir=2;
		}
		else
		{
			curx+=dx;
			cury-=dx;
			dir=3;
		}
		break;

	case 2:
		if(cury<curx)
		{
			curx-=cury+1;
			cury-=cury;
			dir=3;
		}
		else if(cury>curx)
		{
			cury-=curx+1;
			curx-=curx;
			dir=1;
		}
		else
		{
			curx-=curx;
			cury-=cury;
			dir=0;
		}
		break;

	case 3:
		if(dy<curx)
		{
			curx-=dy+1;
			cury+=dy;
			dir=2;
		}
		else if(dy>curx)
		{
			cury+=curx+1;
			curx-=curx;
			dir=0;
		}
		else
		{
			curx-=dy;
			cury+=dy;
			dir=1;
		}
		break;
	}
}
