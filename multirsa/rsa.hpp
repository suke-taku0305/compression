#ifndef _RSA_HPP_
#define _RSA_HPP_

#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

long long powmod(long long b, long long e, long long m );
int gcd(int a, int b);
int lcm(int a, int b);
bool simple(int n);
bool rabin(int n);
vector<bool> eratosthenes(int n);
bool fermat( int n, int trial);
int exgcd( int a, int b);

#endif