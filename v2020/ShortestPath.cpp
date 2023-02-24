
// Gabriele Migliorini, 4ID, 7/10/2020

#include <iostream>
#include <fstream>

using namespace std;

struct arco{
	
	char v1;
	char v2;
	int peso;
};


// Funzioni
// -------------------------------------------------------------------------------------------------------------------------------------------

void carica_dati_grafo(arco a[]);							// Caricamento dei dati relativi al grafo tramite lettura file
void out_grafo();											// Visualizzazione del grafo tramite matrice
void path(char a, char b, arco c[]);						// Algoritmo shortest path
void risultati(char a[], int b, int c);						// Mostra risultati ottenuti
int n_righe_file(char a[]);									// Conta righe di un file.txt
void sposta(char a, char array1[], char array2[]);			// Sposta "a" da "array1[]" ad "array2[]"
bool not_in(char a, char array[]);							// Se "a" non e' presente in "array[]" => return vero, altrimenti: return falso

// -------------------------------------------------------------------------------------------------------------------------------------------


// Variabili globali
// --------------------------------------

char file[9] = "Dati.txt";
const int n_archi = n_righe_file(file);
int n_vertici = 6;
int n_vertici_unvisited = n_vertici;
int n_vertici_visited = 0;
char percorso[20];

// --------------------------------------



int main(){
	
	int k;
	char sn, vP, vA;
	
	arco grafo[n_archi];
	carica_dati_grafo(grafo);
	
	do{
		n_vertici_unvisited = n_vertici;
		n_vertici_visited = 0;
		k = 0;
		
		cout<<"\n\n Rappresentazione del grafo tramite matrice\n\n\n";
		out_grafo();
		cout<<"\n\n";
		
		cout<<" Inserire vertice di partenza: ";
		cin>>vP;
		vP = toupper(vP);
		
		cout<<" Inserire vertice di arrivo: ";
		cin>>vA;
		vA = toupper(vA);
		
		cout<<"\n Shortest path: ";
		
		path(vP, vA, grafo);
		
		cout<<"\n\n\n ____________________________________________________________";
		cout<<"\n\n Vuoi continuare ad utilizzare il programma? [S/n] ";
		cin>>sn;
		
		cout<<"\n ";
		system("PAUSE");
		system("CLS");
	
	}while(sn == 'S' || sn == 's');
	
	cout<<"\n Fine programma.\n";
	
	return 0;
}

void path(char vp, char va, arco a[]){
	
	char unvisited[n_vertici] = {'A', 'B', 'C', 'D', 'E', 'F'}, visited[n_vertici]; 
	char temp, A, B;
	int i, sommatoria_pesi = 0, k = 0;
	
	temp = vp;
	
	do{
		i = 0;
		
		while(i < n_archi){
			
			if((temp == a[i].v1 && not_in(a[i].v2, visited) == true) || (temp == a[i].v2 && not_in(a[i].v1, visited) == true)){
				
				if(temp == a[i].v1){
					
					A = a[i].v1;
					B = a[i].v2; 
					
				}else if(temp == a[i].v2){
					
					A = a[i].v2;
					B = a[i].v1;
				}
				
				sposta(A, unvisited, visited);
				
				percorso[k] = A;
				k++;
				
				sommatoria_pesi += a[i].peso;
				
				temp = B;
				
				i = n_archi;
			}
			
			i++;
		}
		
	}while(temp != va);
	
	percorso[k] = va; 
	
	risultati(percorso, k+1, sommatoria_pesi);
}

void risultati(char a[], int n, int smp){
	
	cout<<" p"<<char(251)<<" = (";
	for(int i=0; i<n; i++){
		
		if(i == n-1)
			cout<<a[i];
		else
		cout<<a[i]<<",";
	}
	cout<<")";
	
	cout<<"   Peso di p"<<char(251)<<" = "<<smp;
	cout<<"\n\n";
}

void sposta(char a, char array1[], char array2[]){
	
	int i=0;
	
	while(i<n_vertici && a != array1[i]){
		
		i++;	
	}
	
	while(i < (n_vertici-1)){
			
		array1[i] = array1[i+1];
		i++;
	}
	
	array2[n_vertici_visited] = a;
	
	n_vertici_unvisited--;
	n_vertici_visited++;	
}

bool not_in(char a, char array[]){
	
	for(int i=0; i<n_archi; i++){
		
		if(a == array[i])
			return false;
	}
	
	return true;
}

int n_righe_file(char file[]){
	
	ifstream f;
	f.open(file);
	string s;
	int i = 0;
	
	if(!f){
		
		cout<<"\n Attenzione, errore apertura file '"<<file<<"'\n\n ";
		system("PAUSE");
		cout<<"\n";
		exit(2);
		
	}else{
	
		while(!f.eof()){
			
			++i;
			getline(f, s, '\n');
		}
	}
	
	f.close();
	
	return i;
}

void carica_dati_grafo(arco a[]){
	
	ifstream file;
	file.open("Dati.txt");
	
	int i = 0;
	
	if(!file){
		
		cout<<"\n Attenzione, errore apertura file '"<<file<<"'\n\n ";
		system("PAUSE");
		cout<<"\n";
		exit(1);
		
	}else{
	
		while(!file.eof()){
			
			file >> a[i].v1 >> a[i].v2 >> a[i].peso;
			++i;
		}
	}
	
	file.close(); 
}

void out_grafo(){
	
	int g[n_vertici][n_vertici] = {

        {0,2,1,5,-1,-1},
        {2,0,2,3,-1,-1},
        {1,2,0,3,1,-1},
        {5,3,3,0,1,5},
        {-1,-1,1,1,0,2},
        {-1,-1,-1,5,2,0}
    };
    
    string vertici = "ABCDEF";
	
    cout<<"\t\t[A]\t[B]\t[C]\t[D]\t[E]\t[F]";
    cout<<"\n\n";
    
    for(int i=0; i<n_vertici; i++){

        cout<<"\t["<<vertici[i]<<"]\t";

        for(int j=0; j<n_vertici; j++){

            if(g[i][j] == -1){

                cout<<" -"<<"\t";
                continue;
            }
            cout<<" "<<g[i][j]<<"\t";
        }
        cout<<"\n\n";
    }
}



