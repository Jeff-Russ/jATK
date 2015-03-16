//
//  main.cpp
//  jATK-CL
//
//  Created by jefrus on 3/16/15.
//  Copyright (c) 2015 Jeff-Russ. All rights reserved.
//

#include <iostream>
#include "/Users/jefrus/git/jATK/Source/jATK/CAArray.h"

using namespace jATK;
using namespace std;



int main(int argc, const char * argv[])
{

    CAArray buffer (10);
    
    for (Audio i = 1; i < 21; i++ )
    {   buffer.record ( i );
        cout <<endl<<i<<'\t';
        
        cout << buffer.getDelaySample4x(2.5);
    }
    cout <<endl<<buffer.getSize();
    return 0;
}

