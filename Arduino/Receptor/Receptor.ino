/* Proyecto "Vitamina C"
 * Primera versión: 10 de marzo del 2020
 * Ultima modificación: 8 de abril del 2020
 * Programa del receptor de radio
 * __________________________
 * ADVERTENCIAS:
 * -Este programa por ahora solo recibe los mensajes, y los muestra por el monitor serie,
 * todavía no se ha comunicado con el programa de C.
 * -Ahora se muestran mensajes que sirven a modo de comprobación de que se recibe
 * la señal, pero que para el proyecto habrá que eliminar.
 * __________________________
 * Notas: 
 * -La comprobación de la pérdida de mensajes puede hacerse en el programa de C o en este.
 * (Al hacerlo en C podría hacer que sea más fácil e inmediato mostrar un aviso al usuario).
 * -Este programa no quita ni el número de bloque ni el #· final. El mensaje no se cambia,
 *  se muestra exactamente lo que se recibe.
 * __________________________
 * Este programa utiliza los módulos RF de la banda de 433MHz
 * Los módulos utilizados para las pruebas son del tipo FS1000A (Emisor) y XY-MK-5V (Receptor)*/
#include <VirtualWire.h>

//Pin al que se conecta el receptor
#define receptor 2

//Si esta opción está activada en el emisor, los mensajes se emiten dos veces. Activando esta opción
//en este programa se descartan los mensajes repetidos. (Es útil cuando la señal no llega muy bien y
//algunos mensajes no son recibidos
const boolean dobleenvio = true;

int i;
int bloque;
int anteriorbloque=0;

void setup() {
  vw_setup(3000); //Velocidad de transmisión en bps
  vw_set_rx_pin(receptor); //Establece el pin
  vw_rx_start(); //Comienza la recepción
  Serial.begin(9600); //Inicia puerto serie
  Serial.println("Listo para recibir");
}

void loop() {
  uint8_t entrante[VW_MAX_MESSAGE_LEN]; //Recibe mensaje
  uint8_t longitud = VW_MAX_MESSAGE_LEN; //Recibe lontigud del mensaje
  if (vw_get_message(entrante, &longitud)){ //Verifica si hay mensaje
    if (dobleenvio==false){ //No se envían los mensajes dos veces, por lo que no comprueba si están repetidos
      mensajesperdidos(entrante); //Función que comprueba si se han perdido mensajes y advierte
      anteriorbloque=bloque;
      for (i=0;i<longitud;i++){ //Se muestra el mensaje
         Serial.print((char)entrante[i]);
      }
      Serial.println("\n_________________________________");
    }
    //Si los mensajes se envían dos veces
    else if (dobleenvio==true){
       mensajesperdidos(entrante);
       if (bloque!=anteriorbloque){ //Comprueba si ese bloque ya se ha recibido
          anteriorbloque=bloque;
          for (i=0;i<longitud;i++) //Se muestra el mensaje
              Serial.print((char)entrante[i]);
          Serial.println("\n-------------");
       }
       else {
          //Como el mensaje ya había sido recibido, no lo lee. (Advierte - a modo de comprobación - de que el mensaje ya se había recibido).
          Serial.println("El mensaje ya había sido recibido");
       }
    }
  }
}

void mensajesperdidos(char entrante[]){
       //Primero leo el número de bloque que está llegando
       bloque = ((entrante[0]-'0')*100)+((entrante[1]-'0')*10)+(entrante[2])-'0';
       //Comprueba que entre el mensaje recibido y el anterior recibido no ha habido ninguno que se haya perdido
       //Muestra una advertencia si se han perdido mensajes (los mensajes por el puerto serie son para las pruebas)
       if ((bloque-anteriorbloque)>1){
          Serial.println("ADVERTENCIA:");
          Serial.println("El emisor ha emitido uno o más mensajes que no han sido recibidos");
          Serial.println("Solución: reiniciar");
       }
}
