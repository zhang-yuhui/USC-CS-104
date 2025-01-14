# Problem 1: Runtime Analysis

In Big-$Θ$ notation, analyze the running time of the following four pieces of code/pseudo-code. Describe it as a function of the input (here, $n$).

## Part (a)
  
```C++
void f1(int n)
{
    int i=2;
    while(i < n){
        /* do something that takes O(1) time */
        i = i*i;
    }
}
```

**Run time:** $\Theta（\log \log n）$

**Explaintion:** Since $i$ multiply itself every iteration, it grows in the rate of $2^{2^k}$ after $k^{th}$ iteration. Also, because $i \le n$, by solving $2^{2^i}=n$, we can get the answer.

## Part (b)

```C++
void f2(int n)
{
    for(int i=1; i <= n; i++){
        if( (i % (int)sqrt(n)) == 0){
            for(int k=0; k < pow(i,3); k++) {
              /* do something that takes O(1) time */
            }
        }
    }
}
```

- 