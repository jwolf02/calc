# calc
Command line calculator for simple arithmethic expressions written in C++.  

## Usage
cd calc  
mkdir build  
cmake ..  
make -j 4  
make install (optional)  
calc "(2 - 6) * exp(sqrt(pi)) / (7 * (-8.99))"  
calc "sqrt(exp(e))" "pi * (-16)^2"  

## Supported Functions  

### Basic arithmethic    
+, -, *, /, ^, mod  
### Trigonometrics     
sin, cos, tan, asin, acos, atan  
### Hyperbolics        
sinh, cosh, tanh, asinh, acosh, atanh  
### Exponentials        
sqr, sqrt, cbrt, root, exp  
### Logarithms
log2, log10, ln, log
### Miscelleneous
min, max
### Rounding functions 
ceil, floor, abs, trunc  
### Constants         
e, pi, inf  

## Features


### Batch mode 
$ calc "(1 + 2)" "2 * 7 - 1"  
(1) 3  
(2) 13

### Interactive mode 
$ calc  
\> (2 * 7) / 2  
7  
\> quit  

### Variables
$ calc  
\> x = log2(16)  
4  
\> sqrt(x)  
2  
\> quit  
