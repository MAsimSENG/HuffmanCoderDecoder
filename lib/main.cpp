#include "huffmantree.cpp"
#include <iostream>
#include <ostream>
#include <fstream>
#include <map>
#include <optional>
#include <vector>
#include <algorithm>
#include <stdlib.h>
/*
	This function takes the name of the file (optional place holder if input from stdin is used instead)  to 
	be decoded as input 
	and the code to symbol map
	to produce the decoded output file 
	in (optional if the file mode is used) decodedoutput.txt otherwise stdandard output. 

*/
void decode_input(std::string input_file_name,std::map<std::string, char> code_to_symbol,
 bool is_file, std::vector<std::string>vec_input)
{

	if(is_file)
	{
		// file mode
		std::ifstream input_file(input_file_name);
		std::ofstream outputfile("decompressed.txt");
		std::string read_chars=""; 
		bool start_of_input_seen = false;
		for(std::string line; std::getline(input_file,line);)
		{

		if(start_of_input_seen)
			{
				for(auto c:line)
				{
					read_chars = read_chars+c;
					if(code_to_symbol[read_chars])
					{
						outputfile<<code_to_symbol[read_chars];
						read_chars="";
					}
				}

				if(!input_file.eof())
				{
					outputfile<<"\n";

				}

			}

		else if(line =="$;$")
			{
				start_of_input_seen = true;
			}
		
		}

		input_file.close();
		outputfile.close();

	}

	else
		{
			//standard output

		std::string read_chars=""; 
		bool start_of_input_seen = false;
		for(int i=0; i<vec_input.size();i++)
		{

			std::string line = vec_input[i];

			if(start_of_input_seen)
				{
					for(auto c:line)
					{
						read_chars = read_chars+c;
						if(code_to_symbol[read_chars])
						{
							std::cout<<code_to_symbol[read_chars];
							read_chars="";
						}
					}

					if(!(i==vec_input.size()-1))
					{
						std::cout<<"\n";

					}

				}

			else if(line =="$;$")
				{
					start_of_input_seen = true;
				}
		
		}


		}
	

}



/*
	This function takes the compressed input file name (if file mode used)
	otherwise it uses the vector of strings (which is the input from stdin)
	This function returns the map from coding (ie the encoded representation to the symbol ex: 001 maps could map to c) to symbols 
*/

std::map<std::string, char> get_map_from_compressedfile(std::string input_file_name,
	bool is_file,std::vector<std::string> vec_input)
{

	if(is_file)
	{
		// if running in file mode
		bool is_correct_format = false;
		std::ifstream input_file(input_file_name);

		std::map<std::string,char> code_to_symbol; 
		
		bool is_input_non_empty = false;

		for(std::string line;std::getline(input_file,line);)
		{

			if(is_input_non_empty == false && line!="")
			{
				is_input_non_empty = true;
			}
			if(line!="$;$")
			{
				bool semicolonseen = false;
				std::string key =""; 
				char value;
				// go over the chars of the curr line 
				// add all chars to key until ';' is seen
				// the char after ";" is the value
				for(auto c:line)
				{	
					if(c==';' && semicolonseen == false)
					{
						semicolonseen = true;
						continue;
					}
					if(semicolonseen)
					{
						value = c; 
						break;
					}
					else
					{
						key = key+c;
					}
				}
				code_to_symbol[key] = value;
		} 

		else
		{
			is_correct_format = true;
			input_file.close();
			break; 
	
		}
	}

	if(!is_input_non_empty || !is_correct_format)
	{
		std::cout<<"FILE READ IS EMPTY OR DOES NOT EXIST OR THE FILE WAS INCORRECT FORMAT FOR DECODING EXITING NOW\n";
		std::exit(1);
	}

	return code_to_symbol;

	}
	else
	{

		// if running in standard input output mode

		bool is_correct_format = false;

		std::map<std::string,char> code_to_symbol; 

		for(int i=0;i < vec_input.size(); i++)
		{	
			std::string line = vec_input[i];

			if(line!="$;$")
			{
				bool semicolonseen = false;
				std::string key =""; 
				char value;
				// go over the chars of the curr line 
				// add all chars to key until ';' is seen
				// the char after ";" is the value
				for(auto c:line)
				{	
					if(c==';' && semicolonseen == false)
					{
						semicolonseen = true;
						continue;
					}
					if(semicolonseen)
					{
						value = c; 
						break;
					}
					else
					{
						key = key+c;
					}
				}
				code_to_symbol[key] = value;
		}  

		else
		{
			is_correct_format = true;
			break; 
	
		}


	}

	if(!is_correct_format)
	{
		std::cout<<"THE INPUT WAS HAS INCORRECT FORMAT FOR DECODING EXITING NOW\n";
		std::exit(1);
	}

		
		return code_to_symbol;

	
	}

}

std::map<std::string,char> invertMap(std::map<char,std::string> symbol_map)
{		
	std::map<std::string, char> code_to_symbol;

	// convert symbol map to code to symbol map 
	for (const auto& [key, value] : symbol_map) 
	{
		code_to_symbol[value] = key;
    }	

	return code_to_symbol;
}


/*

Takes input of huffman tree symbol to huffenconding map 
and the file name of the input file. 
The function writes the compressesion to the output file titled 
"compressed.txt"
*/

void writeCompression(std::map<char,std::string> symbol_map,
	std::map<std::string,char> code_to_symbol, std::string input,
	bool is_file,std::vector<std::string> vec_input)
{
	if(is_file)
	{
		std::ofstream outputfile("compressed.txt");

	    // Preappending the code to symbol mapping 
	    for (const auto& [key, value] : code_to_symbol) 
		{
	        outputfile << key << ";" << value <<"\n";
	    }
	    outputfile<<"$"<<";"<<"$\n";

	    // now read through all the lines of the file and write the compression 
		std::ifstream input_file(input);
		for(std::string line; std::getline(input_file,line);)
		{
			for(auto c:line)
			{
				outputfile << symbol_map[c];
			}
			if(!input_file.eof())
			{
				outputfile <<"\n";
		
			}
		}

		outputfile.close();
		input_file.close();

	}

	else
	{
		 // write the code to symbol map to the std::out
	    for (const auto& [key, value] : code_to_symbol) 
		{
	        std::cout << key << ";" << value <<"\n";
	    }

	    std::cout<<"$"<<";"<<"$\n";


		for( int i=0; i<vec_input.size(); i++ )
	    {
			std::string input = vec_input[i];

			for(auto c:input)
			{
				std::cout << symbol_map[c];
			}
			std::cout<<"\n";
	    }
	
		
	}
	
}


/*
	takes input the priority queue(minheap)
	and takes input file name to pass it on to the write compression
	fucntion 
	this function calls the buildtree and 
	build dictionary to build the huffman tree
	and to build the mapping dictionary from symbol to 
	its binary encoded representation
*/

std::map<char, std::string> createSymbolMapping(std::priority_queue <data *, 
	std::vector<data*>, myFunctor> pq)
{
	produceHuffManTree p(pq);
	p.buildTree();
	std::map<char, std::string> m;
	m= p.buildDictionary();
	return m; 
}

/*
	This function takes the symbol and its frequency map as input 
	along with the input file name (to be used in write compression)
	this function then creates a prioirty queue that 
	is passed to createSymbolMapping 
*/
std::priority_queue <data *, std::vector<data*>, 
	myFunctor> createNodes(std::map<char,int> symbol_freq_map)
{
	std::vector<data*> data_vec; 

	for (const auto& [key, value] : symbol_freq_map)
	 {
		data_vec.push_back(new data(value,key,true));
    }

 	std::priority_queue <data *, std::vector<data*>, 
	myFunctor> pq; 

 	for (data * n : data_vec) 
 	{
    	pq.push(n);
 	}   

 	return pq; 
	
}

std::map<char, int> createSymbolFreqMap(std::string input,bool is_file,
	std::vector<std::string> vec_input) 
{
	std::map<char, int>	symbol_freq_map;

	if(is_file)
	{
		std::ifstream input_file(input);
		bool is_input_non_empty = false;
		for(std::string line; std::getline(input_file, line);)
		{

			if(is_input_non_empty == false && line!="")
			{
				is_input_non_empty = true;
			}	

			for(auto c:line)
			{
				if(symbol_freq_map[c])
				{
					symbol_freq_map[c] = symbol_freq_map[c] +1; 
				}
				else
				{
					symbol_freq_map[c] =1; 
				}
			}

		}

		if(!is_input_non_empty)
		{
			std::cout<<"FILE READ IS EMPTY NOTHING TO COMPRESS EXITING NOW\n";
			std::exit(1);
		}

		input_file.close();
		return symbol_freq_map; 

	}

	else
	{
		for( int i=0; i<vec_input.size(); i++ )
		{
			std::string input = vec_input[i];

			for(auto c:input)
			{
				if(symbol_freq_map[c])
				{
					symbol_freq_map[c] = symbol_freq_map[c] +1; 
				}
				else
				{
					symbol_freq_map[c] =1; 
				}
			}
		}
	

		return symbol_freq_map; 


	}
	



}



int main(int argc, char*argv[])
{


// the user will enter text directly ie not a file 
if(argc == 2)
{

	std::string input = argv[1];

	/* Running compression mode with 
		user input and not a file 
		1. create symbol to freq map 
		2. create min head of all the leaf nodes (symbols)
		3. build the mapping from symbol to encoded representation of 1's and 0's
		4. Write the compression
		*/


	if( input == "-c")
	{

		bool is_input_non_empty=false;
		std::vector<std::string> input_vector; 
		for(std::string line; std::getline(std::cin, line);)
		{
			if(is_input_non_empty == false && line!="")
			{
				is_input_non_empty = true;
			}

			input_vector.push_back(line);

		}		

		if(!is_input_non_empty)
		{
			std::cout<<"ERROR INPUT IS EMPTY EXITING NOW\n";
			return 1;
		}
		
		std::map<char, int> symbol_freq_map = createSymbolFreqMap("",false,input_vector);

		std::priority_queue <data *, std::vector<data*>, 
		myFunctor> pq =createNodes(symbol_freq_map);
	
	 	std::map<char, std::string> m = createSymbolMapping(pq);
	
	 	std::map<std::string, char> code_to_symbol = invertMap(m);
 	
 		writeCompression(m,code_to_symbol,"",false,input_vector);


	}

	else if(input =="-d")
	{

		bool is_input_non_empty=false;

		std::vector<std::string> input_vector; 
		for(std::string line; std::getline(std::cin, line);)
		{
			if(is_input_non_empty == false && line!="")
			{
				is_input_non_empty = true;
			}	

			input_vector.push_back(line);

		}		

		if(!is_input_non_empty)
		{
			std::cout<<"ERROR INPUT IS EMPTY NOTHING TO DECODE EXITING NOW\n";
			return 1;
		}

		 std::map<std::string,char> code_to_symbol = 
			get_map_from_compressedfile("", false, input_vector);

		 decode_input("",code_to_symbol,false,input_vector);

	}
	else

	{	
		std::cout<<"ERROR the operation mode was not specified.\n";
		std::cout<<"USAGE compression mode : Huffmancoder -c (optional input file name else standard input) \n";
		std::cout << "USAGE docompressing mode: Huffmancoder -d (optional compressed file name else standard input)\n";
		return 0; 
	
	}
}

/*
	if argc=3 this means that we are to read from an input file 
	TODO: throw errror if file not found of that name. 
*/
else if(argc ==3)
{
	std::string command_line_arg1 = argv[1];

	if(command_line_arg1 == "-c")
	{
		std::string input_file_name = argv[2];
		std::vector<std::string> input_vector;


		std::map<char, int> symbol_freq_map = createSymbolFreqMap(input_file_name,true,input_vector);
	
		std::priority_queue <data *, std::vector<data*>, 
		myFunctor> pq = createNodes(symbol_freq_map);

	 	std::map<char, std::string> m = createSymbolMapping(pq);

	 	std::map<std::string, char> code_to_symbol = invertMap(m);


 		writeCompression(m,code_to_symbol,input_file_name,true,input_vector);


	}
	/*
		The file being input is a compressed file. 
		0. get input file 
		1. We must decipher the code to symbol key map 
		2. We must then create an output file called "decoded.txt"	
		3. We must write to that 
	
	*/
	else if(command_line_arg1 == "-d")
	{	
		std::string input_file_name = argv[2];
		std::vector<std::string> input_vector;
	

		std::map<std::string,char> code_to_symbol = 
				get_map_from_compressedfile(input_file_name,true,input_vector);

		decode_input(input_file_name,code_to_symbol,true,input_vector);


	}

	else

	{	
		std::cout<<"ERROR the operation mode was not specified.\n";
		std::cout<<"USAGE compression mode : Huffmancoder -c (optional input file name else standard input) \n";
		std::cout << "USAGE docompressing mode: Huffmancoder -d (optional compressed file name else standard input)\n";
		return 0; 
	
	}


}
else if(argc==1)
{
	std::cout<<"ERROR the operation mode was not specified.\n";
	std::cout<<"USAGE compression mode : Huffmancoder -c (optional input file name else standard input) \n";
	std::cout << "USAGE docompressing mode: Huffmancoder -d (optional compressed file name else standard input)\n";
	return 0; 

}
	return 0; 

	
}