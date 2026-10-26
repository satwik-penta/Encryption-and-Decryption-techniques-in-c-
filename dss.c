#include <stdio.h>

long long power(long long a,long long b,long long m){
    long long r=1;
    a%=m;
    while(b>0){
        if(b%2)r=r*a%m;
        a=a*a%m;
        b/=2;
    }
    return r;
}

long long gcd(long long a,long long b){
    while(b){
        long long t=b;
        b=a%b;
        a=t;
    }
    return a;
}

long long inverse(long long a,long long m){
    long long t=0,nt=1,r=m,nr=a;
    while(nr){
        long long q=r/nr;
        long long temp=t-q*nt;
        t=nt;
        nt=temp;
        temp=r-q*nr;
        r=nr;
        nr=temp;
    }
    if(r!=1)return -1;
    return (t%m+m)%m;
}

int main(){
    long long p,g,x,y,m,k,a,b,inv;
    printf("Enter prime p: ");
    scanf("%lld",&p);
    printf("Enter generator g: ");
    scanf("%lld",&g);
    printf("Enter private key x: ");
    scanf("%lld",&x);
    if(p<5||g<2||g>=p||x<1||x>=p-1){
        printf("Invalid input\n");
        return 0;
    }
    printf("Enter numeric message m (0 to p-1): ");
    scanf("%lld",&m);
    if(m<0||m>=p){
        printf("Invalid message\n");
        return 0;
    }
    y=power(g,x,p);
    printf("Public key y: %lld\n",y);
    do{
        printf("Enter random k (1 to p-2, coprime to p-1): ");
        scanf("%lld",&k);
        if(k<1||k>=p-1){
            printf("Invalid k\n");
            return 0;
        }
    }while(gcd(k,p-1)!=1);
    a=power(g,k,p);
    inv=inverse(k,p-1);
    b=((m-x*a)%(p-1)+(p-1))%(p-1);
    b=(b*inv)%(p-1);
    printf("Signature: (%lld, %lld)\n",a,b);
    if(power(g,m,p)==(power(y,a,p)*power(a,b,p))%p)
        printf("Signature Verified\n");
    else
        printf("Signature Invalid\n");
    printf("Enter message to verify: ");
    scanf("%lld",&m);
    if(m>=0&&m<p&&power(g,m,p)==(power(y,a,p)*power(a,b,p))%p)
        printf("Signature Verified\n");
    else
        printf("Signature Invalid\n");
    return 0;
}