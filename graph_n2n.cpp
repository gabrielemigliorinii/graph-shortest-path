
/*
	data: 
		- 21/02/2023.
	
	descrizione:	
		- Il metodo d() calcola la distanza minima tra un 
		  nodo in input e tutti gli altri nodi del grafo.
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// G = (V,E)  

// type G (grafo) = coppia di oggetti 

// type V (nodi) = insieme di nodi
// type E (links) = insieme di coppie ordinate (che rappresentano i link tra tutti i nodi del grafo)

class Graph {
		
	private:
			
		vector<string> V;
		vector<pair<string,string>> E;
		
	public: 
		
		// Costrutture di default
		Graph()
		{	
			// Insieme V di default
			vector<string> init_V = {"w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7"};
		
			// Insieme E (di coppie ordinate) di default
			vector<pair<string,string>> init_E = {
				{"w7", "w3"},
				{"w3", "w0"},
				{"w2", "w3"},
				{"w3", "w4"},
				{"w4", "w5"},
				{"w5", "w6"},
				{"w1", "w6"},
				{"w1", "w2"},
				{"w0", "w4"},
				{"w0", "w1"}
			};
			
			setV(init_V);
			setE(init_E);
		}
		
		Graph(vector<string> V, vector<pair<string,string>> E)
		{
			setV(V);
			setE(E);			
		}
		
		void setV(vector<string> V)
		{
			this->V = V;
		}
		
		void setE(vector<pair<string,string>> E)
		{
			this->E = E;
		}
		
		vector<string> getV()
		{
			return V;
		}
		
		vector<pair<string,string>> getE()
		{
			return E;
		}
		
		map<string,int> d(string v0)
		{	
			vector<string> visited;
			map<string, int> data;
			
			for (int i=0; i<V.size(); i++)
				data[V.at(i)] = -1;
				
			if (data[v0] != -1) 
			{
				data.clear();
				return data;
			}
			
			data[v0] = 0;
			visited.push_back(v0);
			
			int n = 0, k = 0, size_t = -1;
	
			do
			{	
				n++;			
				size_t = visited.size();	
				
				for (int i=k; i<size_t; i++)
				{
					k = visited.size();
					
					for (int j=0; j<E.size(); j++)
					{
						if (visited.at(i) == E.at(j).first)
						{
							if (find(visited.begin(), visited.end(), E.at(j).second) != visited.end() == false) {
							    visited.push_back(E.at(j).second);
								data[E.at(j).second] = n;
							}
						}
					}
				}
				
			} while (k < visited.size());
		
			return data;
		}
		
		void print_distance(string v0)
		{
			auto m = d(v0);
			
			if (m.size() == 0)
				cout << " Your graph does not contains '" << v0 << "'" << endl;
			else
			{
				cout << "\n\n -------------------- \n";
				for (int i=0; i<V.size(); i++)
					cout << " d(" << v0 << ", " << V.at(i) << ") = " << m[V.at(i)]<< endl;
				cout << " -------------------- \n\n";
			}

		}
};

int main()
{	
	/*
	vector<string> V = {"w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7"};
	
	vector<pair<string,string>> E = {
		{"w7", "w3"},
		{"w3", "w0"},
		{"w2", "w3"},
		{"w3", "w4"},
		{"w4", "w5"},
		{"w5", "w6"},
		{"w1", "w6"},
		{"w1", "w2"},
		{"w0", "w4"},
		{"w0", "w1"}
	};
	
	Graph g(V, E);
	*/
	
	Graph g;
	string v0 = "w6";
	g.print_distance(v0);
	
	return 0;
}



