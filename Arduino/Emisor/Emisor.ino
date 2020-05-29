/* Proyecto "Vitamina C"
 * Abril del 2020
 * Programa del emisor de radio
 * __________________
 * ADVERTENCIA IMPORTANTE:
 * -Todavía no se ha probado la comunicación por el puerto serie con el programa en C.
 * Se ha probado mandando mensajes directamente desde el monitor serie del propio IDE de Arduino.
 * -Ajustar el tiempo de espera entre mensajes y la velocidad de transmisión para obtener mejores resultados
 * __________________
 * Este programa utiliza los módulos RF de la banda de 433MHz
 * Los módulos utilizados para las pruebas han sido módulos del tipo FS1000A (Emisor) y XY-MK-5V (Receptor)
 * __________________
 * El programa manda un 1 al ordenador, para indicarle que está listo para recibir (esto podrá cambiarse más adelante).
 * Entonces el programa recibe bloques de texto desde el ordenador (desde un programa en C)
 * y los manda por radio, hasta una placa de Arduino con un receptor de radio que los leerá
 * y se los mandará a un ordenador.
 * __________________
 * Notas generales:
 * -Los bloques enviados deberán tener una longitud de 90 caracteres o menor.
 * -Los bloques recibidos deben llevar al final "#·" para indicar que termina ahí.
 * -Este programa añade a los bloques de texto un  número de tres cifras que identifica el número de bloque que se está enviando.
 *        (Esto puede permitir que si no se recibe algún bloque, se pueda tener conocimiento de ello).
 *        (Nota: esto no permitirá corregir el fallo porque la comunicación por radio es unidireccional).
 * -Si la señal no llega siempre, se puede activar el doble envío, que repite el envío del bloque y el receptor
 *        lo toma si no había reicbido el primer envío y lo descarta si ya lo había recibido.
 */

#include <VirtualWire.h>
//Defino con constantes los pines a los que se conectan los componentes
#define emisor 2 //Pin de datos del módulo emisor de radio
#define led_verde 4
#define led_rojo 3
#define SIZE 100 //Tamaño del array que guarda los bloques

const boolean dobleenvio = true; //True para enviar dos veces el mensaje (activar también en el receptor para descartar mensajes repetidos).
                                 //Es útil cuando algunos mensajes no son recibidos porque no llega bien la señal
 int bloque=1; //Número de bloque que se está enviando - Se añade en el primer hueco de cada array, así se puede comprobar si falta alguno y sirve para identificar
                    //mensajes repetidos cuando se utiliza doble envío.    
char cadena[SIZE];
void setup(){
  Serial.begin(9600);
  digitalWrite (led_verde, OUTPUT); //Configuro los pines de los leds como salidas
  digitalWrite (led_rojo, OUTPUT);
  vw_setup(3000); //Velocidad de transmisión en bps
               //Cuidado, a velocidades demasiado altas parece que se reduce el alcance de la señal
  vw_set_tx_pin(emisor); //Pin de conexión del emisor
  digitalWrite (led_verde, HIGH);
  digitalWrite (led_rojo, LOW);
}

void loop() {
  //Borra la cadena, recibe un nuevo bloque, cuenta el número de bloque que es, envía el bloque por radio               
  borrar(cadena);
  recibirbloque(bloque, cadena);
  bloque++; //Anota que se ha recibido un bloque de datos
  Serial.println("Enviando");
  enviarbloque(cadena);
  delay (3000);
  if (dobleenvio==true){
    Serial.println("Reenviando");
    enviarbloque(cadena);
    delay (3000);
  }
}

//Función que lee los bloques recibidos por el ordenador
void recibirbloque (int bloque, char cadena[]){
  int i;
  Serial.println("1\n");
  cifras(bloque, cadena); //Escribe el número de bloque al comienzo del array (caracteres i=0, i=1, i=2);
  i=3;
  while (cadena[i-2]!='#'&&cadena[i-1]!='·'&&i<(SIZE+1)){
    if (Serial.available()>0){ //Si hay datos disponibles en el puerto serie
      cadena[i]=Serial.read(); //Los lee y los guarda en la cadena de texto
      i++;
    }
    if (i==SIZE-1&&cadena[SIZE-1]!='·'){
    //Controla que no se exceda el tamaño del array
      Serial.println("Se ha producido un error, excedido el tamaño del array, error en los datos de entrada.");
      Serial.println("Programa terminado, desconectando puerto serie.");
      Serial.end(); //Se desconecta del puerto serie
      digitalWrite (led_verde, LOW);
      while (0==0){ //Bucle infinito en el que se enciende y se apaga el led rojo para indicar que hay un problema
          digitalWrite (led_rojo, HIGH);
          delay (1000);
          digitalWrite (led_rojo, LOW);
          delay (1000);
      }
    }
  }  
}

void enviarbloque(char cadena[]){ //Envía la cadena de texto por radio (Se indica encendido el led rojo y apagando el verde durante los envíos)
  Serial.println(cadena);
  digitalWrite (led_rojo, HIGH);
  digitalWrite (led_verde, LOW);
  vw_send((uint8_t *)cadena, strlen(cadena)); //Realiza el envío
  vw_wait_tx(); //Espera a que se envíe el mensaje
  digitalWrite (led_verde, HIGH);
  digitalWrite (led_rojo, LOW);
}

void cifras (int numero, char arraydestino[]){ //Separo las cifras del número y las escribo en el array (así se escribe el número de bloque en cada mensaje)
  arraydestino[0]=(numero/100)+'0'; //Sumo el cero (en ASCII) para convertirlos en números como caracteres numéricos (del 48 al 57 en la tabla ASCII)
  arraydestino[1]=((numero%100)/10)+'0';
  arraydestino[2]=((numero%100)%10)+'0';
}

void borrar(char cadena []){ //Borra todas las posiciones de la cadena de texto que recibe del ordenador 
  int j;
  for (j=0;j<SIZE;j++){
    cadena[j]=NULL;
  }
}
