//2.	Pasa caracteres a ASCII
int Char_a_ASCII(char pswrd[12], int ASCII[11]);
int Char_a_ASCII(char pswrd[12], int ASCII[11])
{
	int i=0;
	while(i<12)
	{
		ASCII[i]= pswrd[i];
	i++;	
	}		
}

