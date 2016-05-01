#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <float.h>
#include <stdio.h>
//#include "regex.h"
using namespace std;

#ifdef _WIN32
    #include <hash_map>
    #include <hash_set>
    using stdext::hash_map;
    using stdext::hash_multimap;
    using stdext::hash_set;
    using stdext::hash_multiset;
#else
    #if defined (__GNUC__) && ( __GNUC__ <= 2 )
        #include <hash_map>
        #include <hash_set>
        using std::hash_map;
        using std::hash_multimap;
        using std::hash_set;
        using std::hash_multiset;
    #else
        #include <ext/hash_map>
        #include <ext/hash_set>
        using __gnu_cxx::hash_map;
        using __gnu_cxx::hash_multimap;
        using __gnu_cxx::hash_set;
        using __gnu_cxx::hash_multiset;
    #endif
#endif

#ifdef WIN32
#define SETMAX(a, b) a=max(a,b);
#define SETMIN(a, b) a=min(a,b);
#else
#define SETMAX(a, b) a>?=b;
#define SETMIN(a, b) a<?=b;
#endif


typedef __int64 LL;
typedef unsigned __int64 ULL;

typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<unsigned int> VU;
typedef vector<LL> VLL;
typedef vector<ULL> VULL;
typedef vector<double> VD;

typedef vector<VI> MI;
typedef vector<VLL> MLL;
typedef vector<VD> MD;

#define FOR(i, from, upto) for (int i=(from); i<(upto); ++i)
#define FOREACHV(i, v) for (int i=0; i<(int)v.size(); ++i)
#define FOREACHM(i, j, m) FOREACHV(i, m) FOREACHV(j, m[i])


const double PREC=1e-9;
#define FISZERO(x) (fabs(x)<PREC)

#define AS(a) (sizeof(a)/sizeof(a[0]))

// BEGIN CUT HERE
template<class A, class T>
inline T A2V(A& a) {T v(a, a+AS(a)); return v; }

template<class A>
inline VI A2VI(A& a) {return A2V<A, VI>(a); }
template<class A>
inline VD A2VD(A& a) {return A2V<A, VD>(a); }
template<class A>
inline VS A2VS(A& a) {return A2V<A, VS>(a); }

template<typename T>
inline void S2V(const string& s, T& v) { stringstream ss(s); typename T::value_type val; while(ss >> val) v.push_back(val); }
template<class T>
inline void VS2M(const VS& vs, T& m) { unsigned prevSize=m.size(); m.resize(prevSize+vs.size()); for (unsigned i=0; i<vs.size(); ++i) S2V(vs[i], m[i+prevSize]); }

template<class T>
inline void V2S(const T& v, string& s) { stringstream ss; if(v.size()>0) { ss<< v[0]; for(unsigned i=1; i<v.size(); ++i) ss << " " << v[i]; s = ss.str(); } else s=""; }
template <class T>
inline void M2VS(const T& m, VS& vs) { vs.resize(m.size()); for (unsigned i=0; i<m.size(); ++i) V2S(m[i], vs[i]); }

template<class T>
inline void OUT_V(const T& v, ostream& os=cout) { for (unsigned int i=0; i<v.size(); ++i) os << v[i] << " "; }
template<class T>
inline void OUT_Ve(const T& v, ostream& os=cout) { for (unsigned int i=0; i<v.size(); ++i) os << v[i] << endl; }
template<class T>
inline void OUT_M(const T& m, ostream& os=cout) { for (unsigned int i=0; i<m.size(); ++i) {OUT_V(m[i], os); os << endl;} }
template<class A>
inline void OUT_A(const A& a, ostream& os=cout) { for (unsigned int i=0; i<AS(a); ++i) os << a[i] << " "; }

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0 ; i != (int)s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != (int)tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

vector<long long> splitLongInt(const string& s, const string& delim = " ") {
    vector<string> tok = split(s, delim);
    vector<long long> res;
    for (int i = 0; i != (int)tok.size(); i++)
        res.push_back(_atoi64(tok[i].c_str()));
    return res;
}

// END CUT HERE

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != (int)a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}

void eq( int n, double have, double need ) {
    if ( FISZERO(have-need) ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}

template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << (unsigned int)have.size() << " elements; expected " << (unsigned int)need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < (int)have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}

vector<string> fileToLines(const char * path)
{
    vector<string> res;
    char buf[256 * 1024] = "";
    FILE * f = NULL;
    //fopen_s(&f, path, "rt");
    f = _fsopen(path, "rt", _SH_DENYNO);

    if (f == NULL)
    {
        fprintf(stderr, "Failed to open %s\n", path);
    }
    else
    {
        buf[0] = 0;
        while (fgets(buf, sizeof(buf), f))
        {
            int l = (int)strlen(buf);
            if (l > 0 && (buf[l - 1] == 0x0a || buf[l - 1] == 0x0d))
            {
                buf[l - 1] = 0;
                --l;
            }
            res.push_back(string(buf, buf + l));
        }
    }

    if (f != NULL)
    {
        fclose(f);
    }

    return res;
}

