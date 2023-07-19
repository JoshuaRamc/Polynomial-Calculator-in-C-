#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdio.h>

class HunPolynomial
{
private:
	std::vector<int> polynomial;
public:
	HunPolynomial();
	std::vector<int> GetPolynomial();
	HunPolynomial(std::vector<int> new_polynomial);
	void Set(std::vector<int> Polynomial);
	HunPolynomial operator+(HunPolynomial poly2);
	HunPolynomial operator-(HunPolynomial poly2);
	HunPolynomial operator*(HunPolynomial poly2);
	float operator() (float x);

};

std::ostream& operator<<(std::ostream& COUT, HunPolynomial& poly);