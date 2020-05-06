FILE *txt;
int *txtASCII;
 txt=fopen ("encript.txt", "r"); //abrir archivo
char p;
i=0;
 while (!fscanf(txt, &p) == EOF){
 	i++;
 }
 cont=i;
 txtASCII=malloc(sizeof(int)*cont); 	//malloc, punteros
 if (txtASCII==NULL){
 	printf("ERROR");
 	exit(-1);
 }
 i=0;
  while (!fscanf(txt, &p) == EOF){
  	*(txtASCII+i)=p;
 	i++;
 }
 fclose(txt);
