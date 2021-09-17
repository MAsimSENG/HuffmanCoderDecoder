Huffmancode program 

Instruction on how to run program:

The program can be run with cmake as follows:

1 ) Enter the following command for an out of source build:

  cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR

  The $INSTALL_DIR is where you would like the program to be installed. 


2) Navigate to the $INSTALL_DIR directory. 

3) There will be two exectuable programs visible : demo and Huffmancoder 
  - The demo program exhibits a demonstration of the Huffmancoder program. 
  - Huffmancoder is the executable program 
  
Using the Huffmancoder program 
  
  The Huffmancoder program can be run in two modes:
  
  1) Standard input/output mode 
  
     To activate this mode use the program as follows:
     
        -For compression mode use the command line argument -c and then press enter. 
         Then you can enter input that you would like to have compressed. 
         
         Example:  Huffmancoder -c
         
         Example: (with input pipelining and output printed to screen) Huffmancoder -c <input.txt  
         
         Example : (with input and output pipelining) Huffmancoder -c <input.txt >compressed_input.txt
         
        -For decompression mode use the command line argument -d and then press enter. 
        Then you can enter the compressed input that you would ike to have  decompressed. 

         Example:(with no input or output pipelining, input taken from keyboard and output to screen)  
          
         Huffmancoder -d

         Example: (with input pipelining and output printed to screen) 
          
         Huffmancoder -d <compressed_input.txt 
 
         Example : (with input and output pipelining) 
         
         Huffmancoder -d <compressed_input.txt >decompressed_output.txt

         Similarly the program can run both compression and decompression run with outpipelining and input from keyboard. 
    
  2) File input/output mode 
  
     To activate this mode use the program as follows:
        
        -For compression mode use the command line argument -c followed by a space 
         and then a name of a file to read input from.  
         
         Example:  Huffmancoder -c input.txt 
         
         In File input/output mode compression will lead to a file being created titled "compressed.txt". 
          
        -For decompression mode use the command line argument -d followed by a space 
         and then the name of a compressed file. 
          
         Example:  Huffmancoder -d compressed.txt 
         
         In File input/output mode compression will lead to a file being created titled "decompressed.txt". 

  
  
