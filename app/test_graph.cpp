#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "huffmantree.cpp"
#include <queue>
#include <vector>
TEST_CASE("sanity")
{

CHECK(1==1);

}
	


TEST_CASE("Producing a tree")
{

	data* d = new data (1,'d',true);
	data* e = new data (2,'e',true);
	data* f = new data (3,'f',true);
	data* g = new data (4,'g',true);



	std::vector<data*> data_vec; 

	data_vec.push_back(d);
	data_vec.push_back(e);
	data_vec.push_back(f);
	data_vec.push_back(g);


	std::priority_queue <data *, std::vector<data*>, 
	myFunctor> pq; 

	 for (data * n : data_vec) 
	 	{
        	pq.push(n);
     	}
	
	
	produceHuffManTree p(pq);

	p.buildTree();


}

TEST_CASE("BFS Traversal of huffmantree")
{	
	data* d = new data (1,'d',true);
	data* e = new data (2,'e',true);
	data* f = new data (3,'f',true);
	data* g = new data (4,'g',true);


	std::vector<data*> data_vec; 

	data_vec.push_back(d);
	data_vec.push_back(e);
	data_vec.push_back(f);
	data_vec.push_back(g);


	std::priority_queue <data *, std::vector<data*>, 
	myFunctor> pq; 

	 for (data * n : data_vec) 
	 	{
        	pq.push(n);
     	}

		produceHuffManTree p(pq);
		p.buildTree();
		p.buildDictionary();


}



TEST_CASE("Traversal to Dictionary")
{	
	data* d = new data (1,'d',true);
	data* e = new data (2,'e',true);
	data* f = new data (3,'f',true);
	data* g = new data (4,'g',true);


	std::vector<data*> data_vec; 

	data_vec.push_back(d);
	data_vec.push_back(e);
	data_vec.push_back(f);
	data_vec.push_back(g);


	std::priority_queue <data *, std::vector<data*>, 
	myFunctor> pq; 

	 for (data * n : data_vec) 
	 	{
        	pq.push(n);
     	}

		produceHuffManTree p(pq);
		p.buildTree();
		std::map<char, std::string> m;
		
		m= p.buildDictionary();

	for (const auto& [key, value] : m) {
        std::cout << key << " = " << value << "; ";
        std::cout<<"\n";
    }	

}


TEST_CASE("I need to be able to write a representation of the huff tree to the compression file for use in decoding")
{

	data* d = new data (1,'d',true);
	data* e = new data (2,'e',true);
	data* f = new data (3,'f',true);
	data* g = new data (4,'g',true);


	std::vector<data*> data_vec; 

	data_vec.push_back(d);
	data_vec.push_back(e);
	data_vec.push_back(f);
	data_vec.push_back(g);


	std::priority_queue <data *, std::vector<data*>, 
	myFunctor> pq; 

	 for (data * n : data_vec) 
	 	{
        	pq.push(n);
     	}

		produceHuffManTree p(pq);
		p.buildTree();
		std::map<char, std::string> m;
		
		m= p.buildDictionary();

	std::map<std::string, char> code_to_symbol;

	for (const auto& [key, value] : m) 
	{
		code_to_symbol[value] = key;
    }	

    for (const auto& [key, value] : code_to_symbol) 
	{
        std::cout << key << " = " << value << "; \n";
    }	



}


TEST_CASE("Given a compressed input I need to be able to uncompress it ")
{


}