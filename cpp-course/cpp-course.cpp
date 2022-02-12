// cpp-course.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "vanilla_option.h"
#include "payoff_double_digital.h"
#include "simple_matrix.h"
#include "binary_function.h"
#include "matrix.h"


#include "Log.h"
#include "Pointers.h"
#include "References.h"
#include "Player.h"
#include "LogClassExample.h"
#include "Entity.h"
#include "PlayerEntity.h"

void VanillaOptionExample();
void VanillaOptionExample() {
    VanillaOption option;  // Create the vanilla option

  // Calculate the call and put prices
    double call = option.calc_call_price();
    double put = option.calc_put_price();

    // Output the option parameters
    std::cout << "Strike, K: " << option.getK() << std::endl;
    std::cout << "Risk-free rate, r: " << option.getr() << std::endl;
    std::cout << "Time to maturity, T: " << option.getT() << std::endl;
    std::cout << "Spot price, S: " << option.getS() << std::endl;
    std::cout << "Volatility of asset, sigma: " << option.getsigma() << std::endl;

    // Output the option prices
    std::cout << "Call Price: " << call << std::endl;
    std::cout << "Put Price: " << put << std::endl;
}

void PayOffDoubleDigitalExample();
void PayOffDoubleDigitalExample() {
    double D = 10.0; // Lower strike
    double U = 20.0; // Uppert strike

    PayOffDoubleDigital pay(U, D); // Create the double digital payoff

    // Output the payoff for various spot prices
    std::cout << "Spot = 5.0: " << pay(5.0) << std::endl;
    std::cout << "Spot = 15.0: " << pay(15.0) << std::endl;
    std::cout << "Spot = 25.0: " << pay(25.0) << std::endl;
}

void SimpleMatrixExample();
void SimpleMatrixExample()
{
    // Create empty SimpleMatrix of type double
    SimpleMatrix<double> sm(4, 4, 0.0);

    // Output values of the SimpleMatrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << sm.value(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}


int main()
{
    //VanillaOptionExample();
    //PayOffDoubleDigitalExample();
    //SimpleMatrixExample();
    //BinaryFunctionExample();
    QSMatrixExample();
    
    // Log("init");
    //Pointers();
    //References();
    //PlayerExample();
    //ClassStructure();
    //Constructors();
    //Inheritance();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
