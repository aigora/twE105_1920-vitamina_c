unsigned long long binarioADecimal(int T[11], int longitud);
unsigned long long binarioADecimal(int T[11], int longitud)
{
  unsigned long long decimal = 0;
  int multiplicador = 1,i,caracterActual;
  for ( i = longitud ; i >= 0; i--) 
  {
    caracterActual = T[i];
    if (caracterActual == '1') {
      decimal += multiplicador;
    }
    multiplicador = multiplicador * 2;
  }
  return decimal;
}
