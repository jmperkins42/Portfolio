/*
    name: Jonah Perkins 
    date: 8/26/23
    purpose: to implement different methods of finding the gcd of two numbers
*/
using namespace std;
#include <iostream>

int part1(int, int, int*, int*);
int part2(int, int);
int part3bonus(int, int);

int main()
{
    // starting integer variables
    int m, n; // two starting numbers
    int v = 0; // gcd
    int x = 0, y = 0; // int variables for extended euclid's algorithm
    // getting the input from the user
    cout << "\nint m: ";
    cin >> m;
    cout << "\nint n: ";
    cin >> n;
    // outputting the results:
    // part 1
    cout << "\nThe results using the extended euclid's algorithm:";
    v = part1(m, n, &x, &y);
    if (v > 0)
        cout << "\ngcd(" << m << ", " << n << ") = " << v << endl;
    else if (v < 0)
        cout << "\ngcd(" << m << ", " << n << ") = " << -v << endl; 
    else
        cout << "\ngcd(" << m << ", " << n << ") = undefined\n"; 
    if (x != 0 && y != 0)
        cout << "x = " << x << " and y = " << y << " where " << m << "x + " << n << "y = " << v << endl;
    // part 2
    cout << "\nThe results uing a consecutive integer checking algorithm:";
    v = part2(m, n);  
    if (v > 0)
        cout << "\ngcd(" << m << ", " << n << ") = " << v << endl;
    else
        cout << "\ngcd(" << m << ", " << n << ") = undefined\n"; 
    // part 3 (bonus)  
    cout << "\nThe results using the middle-school procedure:";     
    v = part3bonus(m, n);      
    if (v > 0)
        cout << "\ngcd(" << m << ", " << n << ") = " << v << endl;
    else
        cout << "\ngcd(" << m << ", " << n << ") = undefined\n"; 
    return 0;
}

/*  
    P A R T   O N E

    purpose: to implement an algorithm to determine the gcd
    using the extended euclid's algorithm

    args: the two integers m and n that you are finding the gcd of and two other 
    integers to hold the values of x and y such that mx + ny = gcd(m,n)

    returns: the gcd
*/
int part1(int m, int n, int *x, int *y)
{
    // base case
    if (m == 0)
    {
        *x = 0;
        *y = 1;
        return n;
    }
    int x1, y1; // stores the results of the recursive call
    int v = part1(n%m, m, &x1, &y1); // actual recursive call
    *x = y1 - (n/m) * x1; // update x
    *y = x1; // update y
    return v; // return gcd
}

/*
    P A R T   T W O

    purpose: to implement an algorithm to determine the gcd
    by implementing a consecutive integer checking algorithm

    args: the two integers m and n that you are finding the gcd of

    returns: the gcd
*/
int part2(int m, int n)
{
    // if either m or n is negative, we perform the algorithm as if they are both positive
    if (m < 0)
        m = -m;
    if (n < 0)
        n = -n;
    int v = min(m,n); // temporarily makes the gcd the smaller of the two numbers
    // if one or both numbers are == 0
    if (m == 0 && n == 0)
    {// if both are 0, the gcd is undefined
        return 0; 
    }
    if (m == 0) 
    {// if m == 0, then n is the gcd
        return n;
    }
    else if (n == 0)
    {// if n == 0, then m is the gcd
        return m;
    }
    // finding the gcd
    while (v > 1 && ((m % v != 0) || (n % v != 0)))
    {
        v--; // increments the number until we reach 1, or the gcd is found
    }
    return v;
}


/*
    P A R T   T H R E E   *** B O N U S ***  

    purpose: to implement an algorithm to determine the gcd
    using the Middle-school procedure

    args: the two integers m and n that you are finding the gcd of

    returns: the gcd
*/
int part3bonus(int m, int n)
{
    // if either m or n is negative, we perform the algorithm as if they are both positive
    if (m < 0)
        m = -m;
    if (n < 0)
        n = -n;
    if (m == 0 && n == 0)
    {// if both are 0, the gcd is undefined
        return 0; 
    }
    if (m == 0) 
    {// if m == 0, then n is the gcd
        return n;
    }
    else if (n == 0)
    {// if n == 0, then m is the gcd
        return m;
    }
    int v = 1; // gcd variable
    // Using two arrays to hold the factors of each number
    // Assume that each number will have 10 or less total factors
    int arr1[10]; 
    int arr2[10];
    int i = 2; // i is used to check for factors, starting at 2
    int length1 = 0; // used to keep place in the array
    while (m > 1) // finding the factors of m
    {
        if (m % i == 0)
        {
            m = m / i;
            arr1[length1] = i; // adds the factor to the array;
            length1++;
            i = 1; // only sets i to 1 because 
        }
        i++;
    }
    int length2 = 0;
    while (n > 1) // finding the factors of n
    {
        if (n % i == 0)
        {
            n = n / i;
            arr2[length2] = i; // adds the factor to the array;
            length2++;
            i = 1; // only sets i to 1 because 
        }
        i++;
    }
    i = 0;
    int j = 0;
    while (i < length1 && j < length2) //traverse until we reach the end of one of the lists
    {
        // the nice thing about this method is that our lists are in order
        // from least to greatest so we can
        // traverse them at the same time to find like factors
        if (arr1[i] == arr2[j]) // if they are equal, multiply the gcd (1) by the factor
        {                       // and move forward in both lists
            v *= arr1[i];
            i++;
            j++;
        }
        else if (arr1[i] > arr2[j]) // if list1's factor is greater, increment list2
        {
            j++;
        }
        else //if list2's factor is greater, increment list1
        {
            i++;
        }
    }
    return v; // return gcd
}