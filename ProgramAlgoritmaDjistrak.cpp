#include <iostream>
#include <fstream>
#include <limits.h>
#include <string>

using namespace std;
#define size 40

typedef struct 
{
	int matriks[size][size];
	int sf; // ukuran terdefenisi
}GRAF;

//SELECTOR
#define Element(G,i,j) 	(G).matriks[i][j]
#define sf(G)			(G).sf


void BUAT_GRAF(GRAF *G,int x){
/* menentukan batas kolom dan baris GRAF*/
	sf(*G) = x;
}


void INPUT_DARI_FILE(GRAF *G,string namaFile){
/*
	Mengkopi isi matriks dari file eksternal ke dalam program
	Sehingga Graf G akan berisi matriks dari file external

 */
	ifstream input;
	int length;
	input.open(namaFile);
	input >> length;
	BUAT_GRAF(G,length);

	while(!input.eof())
	{
		for(int i = 1 ; i <= sf(*G) ;i++)
		{
			for(int j = 1; j<= sf(*G) ;j++)
			{
				input >> Element(*G,i,j);
				if(Element(*G,i,j)<0)
				{
					/*  Element G <0 : tidak ada sisi 
						Element G < 0 akan di isi nilai INT_MAX
					 */
					Element(*G,i,j) = INT_MAX ;
				}
			}
		}
	}
	input.close();
}

//print graf ke layar
void printGraf(GRAF G){

	for (int i = 1; i <= sf(G);i++)
	{
		for (int j = 1; j <= sf(G); j++)
			cout<<Element(G,i,j)<< " ";
		cout<<endl;
	}
}

 void cetaksatu(int jarak[],int e,int a){

 	cout<<"Jarak terpendek dari simpul "<<a<< " ke simpul "<<e <<" : ";
 	cout<<jarak[e]<<endl;
 	 
 }

 void cetak(int jarak[],int e){

 	cout<<"Simpul \t Jarak dari awal : "<<endl;
 	 for (int i = 1; i <= e ; i++){
 	 	if(jarak[i]==0){
 	 		cout<<i<<"\t"<<"Awal"<<endl;	
 	 	}else{
 	 		cout<<i<<"\t"<<jarak[i]<<endl;	
 	 	}
 	 	
 	 }
 }

int jarakMinimum(int jarak[], bool statusJarak[],int e){

	int idxmin,min = INT_MAX;
	for (int i = 1; i <= e; i++)
	{
		if(statusJarak[i]!=true && jarak[i]<min){
			min = jarak[i];
			idxmin = i;
		}
	}
	return idxmin;

}

void Djistrak(GRAF G, int asal){
	int e =sf(G);
	/**/
	int jarak[e]; //output. menampung jarak terpendek
	bool statusJarak[e]; // status jarak terpendek, true jika merupakan jarak terpendek
	int edge[e] ;
	int s;
	
	cout<<"Posisi Akhir  : ";
	cin>>s;	

	/*inisialisasi semua jarak menjadi infinity*/
	for (int i = 1; i <=e; i++)
	{
		jarak[i]=INT_MAX;
		statusJarak[i] = false;
		edge[i]=-1;
	}

	/* jarak asal -> asal = 0*/
	jarak[asal] = 0;

	for (int i =1; i <= e-1; i++)
	{
		int n = jarakMinimum(jarak,statusJarak,e);

		statusJarak[n] = true;

		for (int j = 1; j <= e; j++)
		{
			if(!statusJarak[j] && Element(G,n,j) 
				&& jarak[n] != INT_MAX
				&& jarak[n] + Element(G,n,j) < jarak[j] 
			){
				jarak[j] = jarak[n] + Element(G,n,j);
				edge[n]=j; // menyimpan sisi

			}


		}
	}
	
	
	
	cetak(jarak,e);
	cout<<"\n";
	cetaksatu(jarak,s,asal);
	for (int i = 1; i <=e; ++i)
	{
		if(edge[i]!=-1){
			cout<<i<<edge[i]<<endl;
		}
	}
}



int main()
{
	GRAF G;
	string namaFile;
	int s;
	namaFile="graf.txt";

	INPUT_DARI_FILE(&G,namaFile);
	cout<<"Posisi Awal : ";
	cin>>s;
	Djistrak(G,s);

	return 0;
}

