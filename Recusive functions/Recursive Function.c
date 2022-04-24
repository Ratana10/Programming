// Recursive function

//Sum = 1+2+3+ ... +n
int sum(int n)
{
    if(n == 1)  
        return 1;
    else
        return n+sum(n-1);
}

//Sum = 1+3+5+ ... + 2n-1
int sum(int n)
{
    if(n == 1)
        return 1;
    else 
        return (2*n-1)+ sum(n-1);
}

//Sum = 2+4+6+8+ ... +2n
int sum(int n){
    if(n==1)
        return 2;
    else
        return (2*n)+sum(n-1);
}

//Sum = a^1+a^2+a^3 +...+a^n
int sum(int a, int n){
    if(n==1)
        return a;
    else 
        return pow(a,n)+ sum(a,n-1);
}
//===================
int mul(int n, int a){
    if(n==1)
        return a;
    else
        return a*mul(n-1,a);
}
int sum(int a, int n){
    if(n==1)
        return a;
    else
    {
        int p = mul(n,a);
        return p*mul(a,b);
    }
        
}

//Sum = 2+5+8+ ... + 3n-1
int sum(int n){
    if(n == 1)
        return 2;
    else
        return (3*n-1) + sum(n-1);
}

//Sum = a+b
int sum(int a, int b){
    if(a == 0)
        return b;
    else
        return 1+sum(a-1,b);
}

//Mul = axb
int mul(int a, int b){
    if(a==1)
        return b;
    else
        return b+mul(a-1,b);
}

//Mul = a^n     (a>0, a!=1)
int mul(int a,int n){
    if(n==1)
        return a;
    else
        return a*mul(a,n-1);
}


//Find pgcd of two number
int pgcd(int a, int b)
{
    if(a == b)
        return a;
    else if(a>b)
        return pgcd(a-b,b);
    else
        return pgcd(a,b-a);
}

//Sum = a[1]+a[2]+a[3]+ ... + a[n]
int sum(int a[], int n)
{
    if(a == 1)
        return a[1];
    else
        return a[n]+ sum(a,n-1);
}


