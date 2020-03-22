/*    Código para a automatização da contagem de tempo da competição de seguidor de linha
 *     utilizando o fotosensor.
 *     Feito por: Luan Rocha
 *     Raitec / Detec
 */

#include <avr/interrupt.h> 
#include <avr/io.h>

#define parameter 400 //Parametro de controle da proximidade
#define fine 500      // tempo (milisegundos) de debito por usar o checkpoint


void   resetMillis();   // Função que zera o tempo da função milis();
void SerialInterrupt(); // Função que realiza a função de resetar o sistema ou recebe a informação que o carrinho saiu do circuito.
String readSerial();    // Função que retorna a leitura de uma string da serial 

unsigned long int timecheck1 = 0, timecheck2 = 0, timecheck3 = 0,timecheck4 = 0,timecheck5 = 0,timecheck6 = 0,timefinish = 0, timestart = 0;
char buf;
const byte start  = 2;
const byte check1 = 4;
const byte check2 = 5;
const byte check3 = 6;
const byte check4 = 7;
const byte check5 = 8;
const byte finish = 3;
extern volatile unsigned long timer0_millis;
int c = 1;
String control;

void setup() {
  interrupts(); 
  Serial.begin(9600); 
  Serial.println("Iniciar corrida?\n\r");

  while(1){   
    //espera o comando para iniciar o percurso
    if(Serial.available() >= 3){
      control = readSerial();
      Serial.println(control);
    if(control == "Sim"){
      break;
    }else{
      Serial.println("Coddigo errado.");
    }   }
  }

  
  Serial.println("Esperando o carrinho.");
  while(1){  
    //começa a contar o tempo quando o carrinho sai do inicio
    if(analogRead(A0) >= parameter){
    //if(digitalRead(A0) == LOW){
      resetMillis();
      Serial.println("START");
      Serial.end(); //limpa o buffer da serial
      Serial.begin(9600);
      break; 
  }
}

}
void loop() {
  switch(c){
    // Cada caso corresponde a um checkpoint que o carrinho esta. A contagem de tempo é feita de checkpoint em checkpoint
    // e é enviada pela serial. 
    case 1:
      while(1){
          if(analogRead(A1) <= parameter){ 
            timecheck1 += millis();
            resetMillis();
            Serial.print("Check 1->");
            Serial.println(timecheck1);
            break;
      }  
      if(Serial.available()==3){
        //Avalia se existe uma informação no buff da serial. Caso tenha, chama a função SerialInterrupt e sai do laço
        SerialInterrupt();
        break;
      }   }
        c++;
      break;
    
    case 2:
      while(1){
       if(analogRead(A2) <= parameter){ 
          timecheck2 += millis();
          resetMillis();
          Serial.print("Check 2->");
          Serial.println(timecheck2);
          resetMillis();
          break;
      }
      if(Serial.available()==3){
        SerialInterrupt();
        break;
      }      }
      c++;
      break;
/*
    case 3:
      while(1){
        if(analogRead(A3) <= parameter){ 
          timecheck3 += millis();
          resetMillis();
          Serial.print("Check 3->");  
          Serial.println(timecheck3);
          break;
      }
      if(Serial.available()==3){
        SerialInterrupt();
        break;
      }      }
      c++;
      break; 
      */
    //case 4:
      case 3:
      while(1){
        //Fim do percurso. O tempo final e total é computado e enviado pela serial. Depois de 10 segundos o arduino é resetado.
        if(analogRead(A0) <= parameter){
          timefinish += millis();
          Serial.print("Final->");
          Serial.println(timefinish);
          Serial.println("Final de percurso!");
          Serial.print("Tempo final:  ");
          Serial.println(timecheck1 + timecheck2 + timecheck3 + timecheck4 + timecheck5 + timefinish);
          delay(10000);
          
          asm volatile (" jmp 0");
    }  }
    c = 1; 
      break;     
  } }
  

  void resetMillis(){
    //Reseta a contagem da função milis();
    noInterrupts ();
    timer0_millis = 0;
    interrupts ();
  }

void SerialInterrupt() {
  // analisa o conteudo enviado pela serial e efetua uma determinada operação
  control = readSerial();
  if(strstr(control.c_str(),"STP") != 0){
        Serial.println("->PARAR");
        switch (c){
          case 1: 
            asm volatile (" jmp 0");
            break;
          case 2: 
            while(1){
              if(analogRead(A1)< parameter){
                while(analogRead(A1) <= parameter);
                Serial.println("->RECOMEÇO");
                resetMillis();
                timecheck2 += fine;
                c--;
                break;
              }  
            }
            break;
            
          case 3: 
            while(1){
              if(analogRead(A2)< parameter){
                while(analogRead(A2) <= parameter);
                Serial.println("->RECOMEÇO");
                resetMillis();
                timecheck3 += fine;
                c--;  
                break;
              }
            }
            break;
            
          case 4: 
            while(1){
              if(analogRead(A3)< parameter){
                while(analogRead(A3) <= parameter);
                Serial.println("->RECOMEÇO");
                resetMillis();
                timecheck2 += fine;
                c--;
                break;
              }
          }
          break;
      }
  }
  else if(strstr(control.c_str(),"RST") != 0){
        Serial.println("->RESETAR");
        asm volatile (" jmp 0");
      }
  else{
        Serial.println("-> codigo errado");
       }
       }  
      



String readSerial() {
 String inData = "";
 if (Serial.available() > 0) {
   int h = Serial.available();
   for (int i = 0; i < h; i++) {
     inData += (char)Serial.read();
     inData;
   }
   return inData+"\0";
 }else {
   return "No connection";
 }
}



