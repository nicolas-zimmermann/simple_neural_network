# simple_neural_network
This project is an exercice aiming to create a simple but efficient neural network builder in the C programming language.
To this day it is under developpement, refer to the to-do section of this file to see the advancement of the project.
The initial training set is freely inspired by Yann LeCun, Corinna Cortes and Christopher J.C Burges early work, available at this location : http://yann.lecun.com/exdb/mnist/index.html


# to-do
  
Each function of the code is commented
  

# Actual use of the program

The code is so far singly contained in the main.c file.  
Compile it with gcc using the -lm argument.  

**2 files are used by this program : data and labels

data : data contains 28px * 28px images of grey-leveled pixels  
labels : each bytes of label is a value inbetween 0-9, corresponding to the image's depiction in the data file  

More details considering these files are avaible at the following location : http://yann.lecun.com/exdb/mnist/index.html



data file structure :  
[offset] [type]          [value]          [description]  
0000     32 bit integer  0x00000803(2051) magic number  
0004     32 bit integer  60000            number of images  
0008     32 bit integer  28               number of rows  
0012     32 bit integer  28               number of columns  
0016     unsigned byte   ??               pixel  
0017     unsigned byte   ??               pixel  
........  
xxxx     unsigned byte   ??               pixel  

Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black). 


labels file strucure :  
[offset] [type]          [value]          [description]  
0000     32 bit integer  0x00000801(2049) magic number (MSB first)  
0004     32 bit integer  60000            number of items  
0008     unsigned byte   ??               label  
0009     unsigned byte   ??               label  
........  
xxxx     unsigned byte   ??               label  

The labels values are 0 to 9. 
