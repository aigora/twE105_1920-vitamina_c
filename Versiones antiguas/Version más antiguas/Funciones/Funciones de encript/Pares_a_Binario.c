//Pares a binario
int ASCII_a_01(int X[11],int Y[11],int Z[11]);
{
  int i=0;
    while(i<12)
        {
  	        if(X[i]%2==0)
  	            X[i]=0;
        	else
     	        X[i]=1;
	        
	          
			if(Y[i]%2==0)
  	            Y[i]=0;
	        else
	            Y[i]=1;
	        
	  
	        if(Z[i]%2==0)
  	            Z[i]=0;
	        
	        else
	            Z[i]=1;
	        
	    i++;
        }
  return 0;
}

