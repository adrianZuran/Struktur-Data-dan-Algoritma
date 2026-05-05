// no. 6

int DigitSum(int n1)
{
    if(n1 == 0)
        return 0;
         
    return ((n1 % 10) + DigitSum(n1 / 10));//calling the function DigitSum itself
}
 
// no. 8
int MaxElem(int arr1[])
{
    static int i=0,hstno =-9999;
    if(i < n)
    {
         if(hstno<arr1[i])
           hstno=arr1[i];
      i++;
      MaxElem(arr1);//calling the function MaxElem itself to compare with further element
    }
    return hstno;
}

// no. 10
#include<stdio.h>
int findFactorial(int);

int main()
{

int findFactorial(int n)
{
   if(n==1)
       return 1;
   else
       return(n*findFactorial(n-1));// calling the function findFactorial to itself recursively
 }
