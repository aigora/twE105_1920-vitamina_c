//Funcion desplazamiento
int Func_Desplz(int X[11],int Y[11],int Z[11],int T[11]);
int Func_Desplz(int X[11],int Y[11],int Z[11],int T[11])
{
	int comodin2[11], comodin3[11], comodin4[11];
	int i=0;
		while (i<=11)
		{ 
			comodin2[i]=Y[i];	
			Y[i]=X[i];			
			comodin3[i]=Z[i];
			Z[i]=comodin2[i];
			comodin4[i]=T[i];
			T[i]=comodin3[i];	
			X[i]=comodin4[i];
			i++;	
		}
	return 0;
}
