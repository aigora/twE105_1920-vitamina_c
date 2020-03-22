		
void igualdad (int UDC [11]);
void igualdad (int UDC [11])
{
		int X[11], Y[11], Z[11],T[11], comodin2[11], comodin3[11], comodin4[11];
	int i;
		
		while (i<12){  
			comodin2[i]=Y[i];	
			Y[i]=X[i];			
			comodin3[i]=Z[i];
			Z[i]=comodin2[i];
			comodin4[i]=T[i];
			T[i]=comodin3[i];	
			X[i]=comodin4[i];
			i++;	
		}
}	
