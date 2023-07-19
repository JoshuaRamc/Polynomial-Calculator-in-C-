#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdio.h>
#include "HunPolynomial.h"
//Author: Joshua Ramcharan
//Any unauthorized use of this code is subject to prosecution

HunPolynomial::HunPolynomial()
{
    polynomial = {};
}


HunPolynomial::HunPolynomial(std::vector<int> new_polynomial)
{
    polynomial = new_polynomial;
}

void HunPolynomial::Set(std::vector<int> Polynomial)
{
    polynomial = Polynomial;
}

std::vector<int> HunPolynomial::GetPolynomial()
{
    return polynomial;
}


HunPolynomial HunPolynomial::operator+(HunPolynomial poly2)
{
    HunPolynomial sum;
    if (polynomial.size() > poly2.polynomial.size())
    {
        int difference = polynomial.size() - poly2.polynomial.size();
        for (size_t i = 0; i < difference; i++)
        {
            sum.polynomial.push_back(polynomial[i]);
        }
        int temp_sum;
        for (size_t x = 0; x < poly2.polynomial.size(); x++)
        {
            temp_sum = poly2.polynomial[x] + polynomial[x + difference];
            sum.polynomial.push_back(temp_sum);
            temp_sum = 0;
        }
        return sum;
    }

    else if (poly2.polynomial.size() > polynomial.size())
    {
        int difference = poly2.polynomial.size() - polynomial.size();
        for (size_t w = 0; w < difference; w++)
        {
            sum.polynomial.push_back(poly2.polynomial[w]);
        }
        int temp_sum;
        for (size_t y = 0; y < polynomial.size(); y++)
        {
            temp_sum = polynomial[y] + poly2.polynomial[y + difference];
            sum.polynomial.push_back(temp_sum);
            temp_sum = 0;
        }
        return sum;
    }

    else if (poly2.polynomial.size() == polynomial.size())
    {
        int temp_sum;
        for (size_t j = 0; j < polynomial.size(); j++)
        {
            temp_sum = poly2.polynomial[j] + polynomial[j];
            sum.polynomial.push_back(temp_sum);
            temp_sum = 0;
        }
        return sum;
    }
    return sum;
}

HunPolynomial HunPolynomial::operator-(HunPolynomial poly2)
{
    HunPolynomial difference;
    if (polynomial.size() > poly2.polynomial.size())
    {
        int size_difference = polynomial.size() - poly2.polynomial.size();
        for (size_t i = 0; i < size_difference; i++)
        {
            difference.polynomial.push_back(polynomial[i]);
        }
        int temp_diff;
        for (size_t x = 0; x < poly2.polynomial.size(); x++)
        {
            temp_diff = polynomial[x + size_difference] - poly2.polynomial[x];
            difference.polynomial.push_back(temp_diff);
            temp_diff = 0;
        }
        return difference;
    }

    else if (poly2.polynomial.size() > polynomial.size())
    {
        int size_difference = poly2.polynomial.size() - polynomial.size();
        for (size_t w = 0; w < size_difference; w++)
        {
            difference.polynomial.push_back(-poly2.polynomial[w]);
        }
        int temp_diff;
        for (size_t y = 0; y < polynomial.size(); y++)
        {
            temp_diff = polynomial[y] - poly2.polynomial[y + size_difference];
            difference.polynomial.push_back(temp_diff);
            temp_diff = 0;
        }
        return difference;
    }

    else if (poly2.polynomial.size() == polynomial.size())
    {
        int temp_diff;
        for (size_t j = 0; j < polynomial.size(); j++)
        {
            temp_diff = polynomial[j] - poly2.polynomial[j];
            difference.polynomial.push_back(temp_diff);
            temp_diff = 0;
        }
        return difference;
    }
    return difference;
}


HunPolynomial HunPolynomial::operator*(HunPolynomial poly2)
{
    HunPolynomial product;
    std::vector<int> temp_sums(((polynomial.size() - 1) + (poly2.polynomial.size() - 1)) + 1, 0);
    for (int index = 0; index < polynomial.size(); index++)
    {
        for (int second_index = 0; second_index < poly2.polynomial.size(); second_index++)
        {
            int First_Term_Power= (polynomial.size() - 1) - index;
            int Second_Term_Power = (poly2.polynomial.size() - 1) - second_index;
            int sumPower = (temp_sums.size() - 1) - (First_Term_Power + Second_Term_Power);

          //if we have the resulting final power equal to an already existing power, then we add on to it.
            temp_sums[sumPower] = temp_sums[sumPower] + polynomial[index] * poly2.polynomial[second_index];
        }
    }
    product.polynomial = temp_sums;
  
    return product;
}


float HunPolynomial::operator() (float x)
{
    int current_exponent = polynomial.size() - 1;
    float sum;
    for (size_t i = 0; i < polynomial.size(); i++)
    {
        sum = sum + (polynomial[i] * (pow(x, current_exponent)));
        current_exponent--;
    }

    return sum;
}

std::ostream& operator<<(std::ostream& COUT, HunPolynomial& poly)
{
    std::vector<int> polynomial = poly.GetPolynomial();
    //gets rid of trailing zeros
    for (auto z = polynomial.begin(); z != polynomial.end(); ++z)
    {
        if (*z == 0)
        {
            polynomial.erase(z);
            z--;
        }
        else {
            break;
        }
    }
    int current_exponent = polynomial.size() - 1;
    std::stack<std::string> operators;
    std::string powers = "x^";
    for (int i = polynomial.size() - 1; i >= 0; i--)
    {
        if (i != 0)
        {
            if (polynomial[i] > 0)
            {
                operators.push(" + ");
            }
            else if (polynomial[i] < 0)
            {
                operators.push(" - ");
            }
        }

        else if (i == 0)
        {
            if (polynomial[i] >= 0)
            {
                operators.push("Leading Positive");
            }
            else if (polynomial[i] < 0)
            {
                operators.push("- ");
            }
        }
    }

    for (int j = 0; j < polynomial.size(); j++)
    {
        //for the beginning of a polynomial, like x^3 in x^3+2
        if (j == 0)
        {
            if (operators.top() == "Leading Positive")
            {

                if (polynomial[j] == 1)
                {
                    COUT << powers << current_exponent;
                    operators.pop();
                    current_exponent--;
                }
                else if (polynomial[j] == 0)
                {
                    operators.pop();
                    current_exponent--;
                }
                else if (polynomial[j] > 1)
                {
                    std::cout << polynomial[j] << "*" << powers << current_exponent;
                    operators.pop();
                    current_exponent--;
                }
            }
            else if (polynomial[j] == -1)
            {
                COUT << operators.top() << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }

            else if (polynomial[j] < 1)
            {
                std::cout << operators.top() << std::abs(polynomial[j]) << "*" << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }
        }
        //for the last in polynomial, such as 3 in x^2 + 15*x + 3
        else if (j == polynomial.size() - 1)
        {
            if (polynomial[j] == 0)
            {
                current_exponent--;
            }
            else {
                COUT << operators.top() << std::abs(polynomial[j]);
                operators.pop();
            }

        }
        //for the second to last in polynomial, such as 7 in x^3 + 3*x^2 - 7*x + 20
        else if (j == polynomial.size() - 2)
        {
            if (polynomial[j] == 1 || polynomial[j] == -1)
            {
                COUT << operators.top() << "x";
                operators.pop();
            }
            else if (polynomial[j] == 0)
            {
                //operators.pop();
                current_exponent--;
            }
            else
            {
                COUT << operators.top() << std::abs(polynomial[j]) << "*" << "x";
            }
        }

        else
        {
            if (polynomial[j] == 1)
            {
                COUT << operators.top() << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }
            else if (polynomial[j] == 0)
            {
                current_exponent--;
            }
            else if (polynomial[j] == -1)
            {
                COUT << operators.top() << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }

            else if (polynomial[j] < 1)
            {
                COUT << operators.top() << std::abs(polynomial[j]) << "*" << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }
            else if (polynomial[j] > 1)
            {
                COUT << operators.top() << polynomial[j] << "*" << powers << current_exponent;
                operators.pop();
                current_exponent--;
            }
        }
    }

    return COUT;
}