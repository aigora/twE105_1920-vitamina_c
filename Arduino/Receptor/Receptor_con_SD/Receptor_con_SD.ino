/* Proyecto "Vitamina C"
 * Primera versión: 10 de marzo del 2020
 * Ultima modificación: 15 de mayo del 2020
 * Programa del receptor de radio
 * Nueva versión con capacidad para escritura en tarjeta SD
 * Incluye LEDs indicadores, de manera que se pueda saber en qué estado se encuentra el programa
 * sin tener que estar conectados al puerto serie.
 * (Debido a los problemas con la lectura del puerto serie.
 * Los datos se muestran en el monitor serie correctamente pero no es posible leerlos con el
 * programa de C).
 * __________________________
 * Este programa utiliza los módulos RF de la banda de 433MHz
 * Los módulos utilizados para las pruebas son del tipo FS1000A (Emisor) y XY-MK-5V (Receptor)*/
#include <VirtualWire.h>
#include <SPI.h>
#include <SD.h>


//Pin al que se conecta el receptor
#define receptor 2

//Pin CS de la tarjeta SD
#define sd_pin 10 //el resto de pines de la tarjeta se conectan con normalidad. (ver wiki del proyecto en github).

//Pines a los que se conectan componentes que indican el estado del programa (LEDs y zumbador)
//Estos componentes no son imprescindibles. Son solo indicadores, se puede prescindir de ellos sin necesidad de hacer ningún cambio en el programa
//Se indican los colores utilizados en mayúsculas al final de las siguientes líneas
#define led_sd 3 //Led de actividad de la SD       AZUL
#define led_listo 4 //Led que indica que el programa está esperando recibir una transmisión      VERDE
#define led_recibido 7 //Led que indica que se ha recibido un mensaje       AZUL
#define led_error 5 //Led que indica que ha habido un problema/error      ROJO
#define led_aviso 6 //Led que indica si se ha perdido algún mensaje doble (si se han perdido las dos repeticiones es un error directamente      AMARILLO

//Si esta opción está activada en el emisor, los mensajes se emiten dos veces. Activando esta opción
//en este programa se descartan los mensajes repetidos. (Es útil cuando la señal no llega muy bien y
//algunos mensajes no son recibidos
const boolean dobleenvio = true;
unsigned int i;
unsigned int bloque;
unsigned int anteriorbloque=0;
//char temp [100]; //Vector temporal para los mensajes

void setup() {
  vw_setup(3000); //Velocidad de transmisión en bps
  vw_set_rx_pin(receptor); //Establece el pin
  vw_rx_start(); //Comienza la recepción
  //Declaro como salidas o entradas los pines a los que se conectan los leds, etc
  pinMode (led_sd, OUTPUT);
  pinMode (led_listo, OUTPUT);
  pinMode (led_recibido, OUTPUT);
  pinMode (led_error, OUTPUT);
  pinMode (led_aviso, OUTPUT);
  pinMode (10, OUTPUT);
  Serial.begin(9600); //Inicia puerto serie. Como no ha sido posible realizar una comunicación completa con
                      //el programa en C, el puerto serie se va a utilizar para mensajes de avisos, no para
                      //transmitir los datos por lo que pasa a ser opcional.
  Serial.println("Iniciando SD");
  if (!SD.begin(10)) {
    Serial.println("Error SD. Deteniendo el programa");
    Serial.end();
    while (1){ //Bucle infinito en el que solo enciende y apaga el led rojo
      digitalWrite (led_error, HIGH);
      delay (200);
      digitalWrite (led_error, LOW);
      delay (1000);
      }
  }
  Serial.println("Listo para recibir");
}

void loop() {
  String datos = ""; //Creo un String vacío que va a guardar temporalmente los datos recibidos para guardarlos en la SD después
  digitalWrite (led_listo, HIGH);
  uint8_t entrante[VW_MAX_MESSAGE_LEN]; //Guarda mensaje
  uint8_t longitud = VW_MAX_MESSAGE_LEN; //Guarda la lontigud del mensaje
  if (vw_get_message(entrante, &longitud)){ //Verifica si hay mensaje y lo recibe
    digitalWrite (led_recibido, HIGH);
    digitalWrite (led_listo, LOW);
    if (dobleenvio==false){ //No se envían los mensajes dos veces, por lo que no comprueba si están repetidos
      mensajesperdidos(entrante, bloque, anteriorbloque); //Función que comprueba si se han perdido mensajes y advierte
      anteriorbloque=bloque;
      for (i=0;i<longitud;i++){ //Se muestra el mensaje
         Serial.print((char)entrante[i]);
      }
      Serial.println("\n_________________________________");
    }
    //Si los mensajes se envían dos veces
    else if (dobleenvio==true){
       mensajesperdidos(entrante, bloque, anteriorbloque);
       if (bloque!=anteriorbloque){ //Comprueba si ese bloque ya se ha recibido
          anteriorbloque=bloque;
          for (i=0;i<longitud;i++){ //Se muestra el mensaje
            if (i>2&&i<(longitud-2)){
              Serial.print((char)entrante[i]);
              datos += char(entrante[i]);
            }
          }
          Serial.println("\n-------------");

          //Guarda los datos en el fichero
          digitalWrite (led_sd, HIGH);
          Serial.println("Intentando abrir fichero");
          File fichero = SD.open("datos3.txt", FILE_WRITE);
          if (fichero){
            fichero.println(datos);
            fichero.close();
          }
          else{
            Serial.println("Fichero de datos no disponible");
            digitalWrite (led_error, HIGH);
          }
          digitalWrite (led_sd, LOW);
       }
       else {
          //Como el mensaje ya había sido recibido, no lo lee. (Advierte - a modo de comprobación - de que el mensaje ya se había recibido).
          Serial.println("El mensaje ya había sido recibido");
       }
    }
    delay (1000);
    digitalWrite (led_recibido, LOW);
    digitalWrite (led_listo, HIGH);
  }
}

void mensajesperdidos(char entrante[], int bloque, int anteriorbloque){
       //Primero leo el número de bloque que está llegando
       bloque = ((entrante[0]-'0')*100)+((entrante[1]-'0')*10)+(entrante[2])-'0';
       //Comprueba que entre el mensaje recibido y el anterior recibido no ha habido ninguno que se haya perdido
       //Muestra una advertencia si se han perdido mensajes (los mensajes por el puerto serie son para las pruebas)
       if ((bloque-anteriorbloque)>1){
          Serial.println("ADVERTENCIA:");
          Serial.println("Uno o más mensajes no han sido recibidos");
          Serial.println("Solución: reiniciar");
          digitalWrite (led_aviso, HIGH);
       }
}
