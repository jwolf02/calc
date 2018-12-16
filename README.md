# calc
command line calculator for simple arithmethic expressions written in C++  

## Usage
cd calc  
mkdir build  
cmake ..  
make -j 4  
make install (optional)  
calc "(2 - 6) * exp(sqrt(pi)) / (7 * (-8.99))"  
calc "sqrt(exp(e))" "pi * (-16)^2"  

## Supported Functions  
Basic arithmethic:  {+, -, *, /, ^, mod}  
Trigonometrics:     {sin, cos, tan, asin, acos, atan}  
Hyperbolics:        {sinh, cosh, tanh, asinh, acosh, atanh}  
Miscellaneous:      {sqr, sqrt, cbrt, log2, log10, ln, log, exp, min, max}  
Rounding functions: {ceil, floor, abs}  
Constants:          {e, pi}  

## Miscellaneous  
Note: negative numbers have to be parenthesized (e.g. (-1) or sin(-pi))
