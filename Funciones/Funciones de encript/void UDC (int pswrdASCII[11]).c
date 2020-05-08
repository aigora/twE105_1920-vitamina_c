int UDC (int pswrdASCII[11],int X[11],int Y[11],int Z[11]);
int UDC (int pswrdASCII[11],int X[11],int Y[11],int Z[11])
{
		int i;
		while (i<12)
		{
				Z[i]= pswrdASCII[i]%10;
	            Y[i] = (pswrdASCII[i]-Z[i])%100;
	            X[i]= (pswrdASCII[i]-Z[i]-Y[i])/100;
	            Y[i] /= 10;
	    i++;    
		}		
}
	
	
