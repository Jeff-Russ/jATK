/*
  ==============================================================================

    test.h
    Created: 13 Apr 2015 11:48:16pm
    Author:  jefrus

  ==============================================================================
*/

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>
#include "Noise.h"

using namespace jATK;


void testNoise ()
{   DigitalNoise noise(1);
    for (int i = 0; i < 50; i++) { std::cout << noise() << ' '; }
    for (int i = 0; i < 50; i++) { std::cout << noise.binary() << ' '; }
}


#endif  // TEST_H_INCLUDED
