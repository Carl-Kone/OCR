#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "grid_read.h"
#include "grid_write.h"
#include "sudoku_solver.h"

// The solver program
int main(int argc, const char * argv[])
{
    // Error: if there is more than one argument
    if (argc != 2)
        errx(1,"Error: Enter ONE argument");
    
    const char *path = argv[1];
    FILE *fptr;
    //opening the file for reading
    if ((fptr = fopen(path,"r")) == NULL)
        errx(1,"Error: \"%s\" does not exist",path);
    
    const char *res = grid_read(fptr);
    fclose(fptr);
    
    
    // Solving the Sudoku
    initialise_grid(res);
    solve();
    print();
    
    res = grid_to_string();
   
    
    // store it in a file
   grid_write(res,path);
    
    
    return 0;
    
}
