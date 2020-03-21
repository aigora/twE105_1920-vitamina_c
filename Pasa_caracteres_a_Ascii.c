//2.	Pasa caracteres a ASCII
int Char_a_ASCII(char pswrd[12] );
int Char_a_ASCII(char pswrd[12] )
{
	int i,pswrdASCII[11];
	i=0;
	while(pswrd[i]!='\0')
	{
		pswrdASCII[i]=pswrd[i];
	}
	i++;
	return pswrdASCII[11];
}

