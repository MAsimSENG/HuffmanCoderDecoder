#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include<string>

struct data
	 {
	 public:
	 	int frequency; 
	 	char dat; 
 		bool leaf_node=false; 
		std::string symbol ="";
		data* _left_child=nullptr;
		data* _right_child=nullptr; 
		bool explored = false; 

	 	data(int freq, char data,bool _leaf_node)
	 	{
	 		frequency = freq;
	 		dat = data; 
	 		leaf_node = _leaf_node;
	 		_left_child = nullptr;
	 		_right_child = nullptr;
	 	}
	 	data(int freq, data* left_child, data* right_child)
	 	{
	 		frequency = freq;
	 		dat = 'z'; 
	 		_left_child = left_child;
	 		_right_child = right_child;
	 	}
	 	data(const data* other)
	 	{
	 	  	dat = other->dat;
	 		frequency = other->frequency;
	 		_left_child = other->_left_child;
	 		_right_child = other->_right_child;
	 		leaf_node = other->leaf_node;
	 		symbol = other->symbol;

	 	}

 
	 	data operator=(const data* other) 
	 	{
	 		dat = other->dat;
	 		frequency = other->frequency;
	 		_left_child = other->_left_child;
	 		_right_child = other->_right_child;
	 		leaf_node = other->leaf_node;
	 		symbol = other->symbol;

	 		return this; 
	 	}



	 	char dataa()const 
	 	{
	 		return dat;
	 	}
	 	int freq()const
 		{
 			return frequency;
 		}
	};

	class myFunctor
	{
		public:

		bool operator()(const  data* d1,
		  const data *  d2) const
		{
			return (d1->freq()) > (d2->freq());
		}
	};


class produceHuffManTree{
public:

	produceHuffManTree( std::priority_queue<data*,
	 std::vector<data*>, myFunctor> pq): _pq(pq){}
	
	void buildTree()
	{

		 while (_pq.size() > 1)
			{	

		 		 data * left_child = new data(_pq.top());

		    	_pq.pop();

		 		 data * right_child = new data(_pq.top());

		    	_pq.pop();
		    	
		    		data* n = new data( left_child->freq() + right_child->freq(),
		    		left_child,right_child);

		    	_pq.push(n);

			}

	}


	/*
		This function needs to traverse the huffman tree 
		and create a mapping between the symbol at the leaf and 
		the traversal 
	*/
	std::map<char, std::string> buildDictionary()
	{

		// have to loop over all the nodes 
		std::queue<data*> data_queue; 
		data * root = _pq.top();
		root ->explored = true; 
		data_queue.push(root);

		std::map<char, std::string> dictionary; 


		while(data_queue.empty() == false)
		{

			data * curr_node = data_queue.front();
			data_queue.pop();


			if(curr_node->leaf_node == true)
			{
				dictionary[curr_node->dataa()] = curr_node->symbol;
	
			}

			for(int i=0; i<2;i++)
			{
				if(i==0)
				{

					if(curr_node->_left_child && curr_node->_left_child->explored==false)
					{
						curr_node->_left_child->explored = true; 
						curr_node->_left_child->symbol = curr_node->symbol + "0";
						data_queue.push(curr_node->_left_child);


					}

				}
				if(i==1)
				{
					if(curr_node->_right_child && curr_node->_right_child->explored==false)
					{
						curr_node->_right_child->explored =true;
						curr_node->_right_child->symbol = curr_node->symbol + "1";
						data_queue.push(curr_node->_right_child);

					}	
				}
			}

		}

		_dictionary= dictionary;

		return _dictionary;
	}
private:
	std::priority_queue<data*,std::vector<data*>, myFunctor> _pq; 	
	std::map<char, std::string> _dictionary; 

};

