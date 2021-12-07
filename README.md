# OCR- SUDOKU SOLVER
THIS IS A REPOSITORY FOR THE CODE OF OUR PROGRAM THAT IS ABLE TO RECOGNISE A SUDOKU GRID IN AN IMAGE, SOLVES IT, THEN RETURN AN IMAGE OF THE SOLUTION.

Find below instructions on how you can run the app and explanations on the different folders.

# To be known
  • Implemented using the **C** language.  
  • UI implemented using **GTK** framework with **glade**.  
  • Image operations implemented using **SDL**, **SDL_Image** and **SDL_gfx**.  
  • All **Makefiles** are maid available for each folder.
	• Implented the Hough algorithm for line detection, as well as a Neural Network for recognising digits.  
	
# How to run the app ?
• Open a terminal and move to the **UI** folder. Then enter**make** with the provided Makefile.   
• Make sure you have all the required libraries in orther to compile the code ( SDL,GTK..) view the makefile for clarification.
• Once the UI opened, you can use the images provided in **Sample Images** in order to run the application.


# UI Folder explained
This is the most important folder. It is where the GUI is and it makes use of all the other folders. After compiling (Makefile already provided), you just need to run (./user_interface) in order to display the UI and hence use the program.
	
# Image Folder explained
Here is where all the preprocessing and detection is doneof the image is done. i.e, applying filters, implementing the hough transform, detecting lines, detecting the grid and splliting the image into 81 different images( 81 cells in Sudoku)for the neural network. This folder has a main. feel free to run it in order to understand the different functions within the scope of the folder.

# NeuralNetwork Folder explained
Here was implemented all the functions necessary for the recognition of the digits of the grid. This folder has a main. feel free to run it in order to understand the different functions within the scope of the folder.

# Solver Folder explained
In this folder, the algorithm for solving any given Sudoku was written. it takes in a text file of a **grid format** and gives out a text file with the solved grid. There is also a main.c in this folder so feel free to run it in order to understand the different functions within the scope of the folder. The main takes one argument which is the path for the text file. In **Sample_Images_Text** are some sample grids in text file. Pass one of these grids as parameter  to the main excecutable (after having **make**) or feel free to create your own grid.
  
  
