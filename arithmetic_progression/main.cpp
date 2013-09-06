#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <ctime>
#include <sys/time.h>

#define mod(m) (m > 1000003) ? m % 1000003 : m
using namespace std;
namespace std {
template<typename a, typename b>
struct hash< pair<a, b> > {
private:
   const hash<a> ah;
   const hash<b> bh;
public:
   hash() : ah(), bh() {};
   size_t operator()(const std::pair<a, b> &p) const {
      return ah(p.first) ^ bh(p.second);
   }
};
} // namespaces

static unsigned long long cache_D[100000];
static unsigned long long cache_d[100000];
static unsigned long long cache_p[100000];
static unordered_map<unsigned long long, unsigned long long> cache_F;           // lookup O(1)
static unordered_map<pair<unsigned long long, unsigned long long>, unsigned long long> cache_P; //use unordered_map 

unsigned long long fact_cache [21] = {

 1                      ,
 1                      ,
 2                      ,
 6                      ,
 24                     ,
 120                    ,
 720                    ,
 5040                   ,
 40320                  ,
 362880                 ,
 3628800                ,
 39916800               ,
 479001600              ,  
 6227020800             ,
 87178291200            ,
 1307674368000          ,
 20922789888000         ,
 355687428096000        ,
 6402373705728000       ,
 121645100408832000     ,
 2432902008176640000                      

};

unsigned long long power(unsigned long long x, unsigned long long y)
{
    pair<unsigned long long, unsigned long long> curr(x, y);
    if(cache_P.find(curr) != cache_P.end())
    {
        return cache_P[curr];
    }
    unsigned long long result = 1;
    unsigned long long mod_x =  mod(x);
    
    while( y )
    {
        if ( y & 1 )
        {
            unsigned long long temp = result *  mod_x;
            result = mod(temp);
        }
        y >>= 1;
        unsigned long long temp = mod_x *  mod_x;
        mod_x =  mod(temp);
    }
    cache_P[curr] = result;

    return result;
}

unsigned long long factorial(unsigned long long x)
{
    if(x <= 20){
        return fact_cache[x];
    }
    if (cache_F.find(x) != cache_F.end())
    {
        return cache_F[x];
    }
    else
    {
        unsigned long long result = 1;
       
        for(unsigned long long i = x; i >= 1; i--)
        {
            if(cache_F.find(i) != cache_F.end())
            {
                unsigned long long temp1 = result * cache_F[i];
                result = mod(temp1);
                cache_F[x] = result;
                return result;
            }
            unsigned long long mod_i = mod(i);
            unsigned long long temp2 = result * mod_i;
            result = mod(temp2);
        }
        cache_F[x] = result;
        return result;
    } 
}


unsigned long long modinv( unsigned long long a) {
    return mod(power(a, 100002)); // ( (a to the totient) mod the modulus )
}


void query(int from, int to)
{
    unsigned long long k = 0;
    unsigned long long constant = 1;

    for(int i = from - 1; i < to; i++)
    {
        k += cache_p[i];
        unsigned long long temp = constant * cache_D[i];
        constant = mod(temp);
    }
    if(k>1000003){
        constant = 0;
    }
    else{
          unsigned long long temp = constant * factorial(k);
          constant = mod(temp);
       
    }
    cout << k <<" " <<constant <<endl;
}

int main() {
    int n;
    cin >> n;
    for(int k = 0; k< n; k++){
        
        unsigned long long a, d, q;
        cin >> a >>d >> q;
        cache_d[k] = d;
        cache_p[k] = q;
        cache_D[k] = power(d, q);
    }
    int q;
    cin >> q;
    int ops=-1;
    int i, j, v;
    int limit = 5;
    bool found;
    unsigned long long K=1;
    unsigned long long V = 0;
    for(int k = 0; k< q; k++){
        cin >> ops>>i>>j;
        
        switch (ops){
            case 0:
                query(i,j);
                break;
           case 1:
            cin>>v;
            for(int x = i - 1; x < j; x++)
            {
                cache_p[x] += v;
                 unsigned long long temp = cache_D[x] * power(cache_d[x], (unsigned long long)v);
                 cache_D[x] = mod(temp);
            }
        }
    }
}
