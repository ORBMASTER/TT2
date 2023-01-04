#include <SoftwareSerial.h>
#include <setjmp.h>
//#include <iostream>
#include <Arduino.h>
SoftwareSerial sim(10,11);
 int decimalPrecision = 2;                   // decimal places for all values shown in LED Display & Serial Monitor

        /* 1- AC Voltage Measurement */
        
        int VoltageAnalogInputPin = A2;             // Which pin to measure voltage Value (Pin A0 is reserved for button function)
        float voltageSampleRead  = 0;               /* to read the value of a sample in analog including voltageOffset1 */
        float voltageLastSample  = 0;               /* to count time for each sample. Technically 1 milli second 1 sample is taken */
        float voltageSampleSum   = 0;               /* accumulation of sample readings */
        float voltageSampleCount = 0;               /* to count number of sample. */
        float voltageMean ;                         /* to calculate the average value from all samples, in analog values*/ 
        float RMSVoltageMean ;                      /* square roof of voltageMean without offset value, in analog value*/
        float adjustRMSVoltageMean;
        float FinalRMSVoltage;                      /* final voltage value with offset value*/
   
        
        /* 1.1- AC Voltage Offset */
        
              float voltageOffset1 =0.00 ;          // to Offset deviation and accuracy. Offset any fake current when no current operates. 
                                                    // Offset will automatically callibrate when SELECT Button on the LCD Display Shield is pressed.
                                                    // If you do not have LCD Display Shield, look into serial monitor to add or minus the value manually and key in here.
                                                    // 26 means add 26 to all analog value measured.
              float voltageOffset2 = 0.00;          // too offset value due to calculation error from squared and square root 
int _timeout;
volatile int watts=0;
volatile int Estado;
//String a[5]={"0","0","0","0","0"};
int a[5]={1,1,1,1,0};
int w[5]={0,0,0,0,0};
jmp_buf exception_mng;
String dato3;
int b=0;
int c=0;
int d=0;
int e=0;
int tam=20;
volatile int tamano=0;
volatile int tamanob=0;
volatile int tamanoc=0;
int Contador=0;
volatile int Bateria=100;
volatile int k=0;
String _buffer;
String nombresusuarios[10];
String numbersusuarios[10];
String sensores[5]={ "100", "200","300","400","500"};
String numbers[5]={ "+524921956667", "+524922917860","+524921956667","+524922917860","+524921956667"};
String numbers2[5]={ "+524921956667", "+524921956667","+524921956667","+524921956667","+524921956667"};
String numbers3[5]={ "+524921956667", "+524922504428","+524921956667","+524922504428","+524921956667"};
//String numbers2[6]={ "+524921956667", "+524921956667","+524921956667","+524921956667","+524921956667","+524921956667"};
String number4 = "+524921956667";
//String number = "+524921716550";
String number2 = "+524921716550";
String Saldo = "333";
//String number2 = "+524922504428";
String number3 ="+524922917860";
String number ="+524921512910";
//
String numberm="+524922917860";
String Mensaje="Energia electrica desactivada";
//  int dispositivos[5]={1,1,1,1,1};
void setup() {
  
 // attachInterrupt(digitalPinToInterrupt(2), apagado, LOW);
 
// attachInterrupt(digitalPinToInterrupt(2), SendMessage, FALLING);
  //attachInterrupt(digitalPinToInterrupt(3), SendMessage2, RISING);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,1);
  digitalWrite(7,1);
  digitalWrite(8,1);
  Estado=1;
    attachInterrupt(digitalPinToInterrupt(2), apagado, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), encendido, RISING);
  // put your setup code here, to run once:
Serial.begin(9600);

      //Serial.write("rd\n");
      //delay(1000);
      //Serial.flush();
     
     // int dispositivos[5]=Serial.read();
    //  Serial.println(Serial.read());
     // for(int i=0;i<5;i++){
       // if(dispositivos[i]==1){
         // a[i]=1;
        //}
        //if(dispositivos[i]==0){
          //a[i]=0;
        //}
      //Serial.flush();
      
   
    
  //}
     // Serial.write("ru\n");
      //while{
        
    //  }
      
_buffer.reserve(50);
Serial.write("rd\n");
delay(1000);
Serial.write("ru\n");
delay(2500);
/*
Serial.print("AT+NAME");
delay(1000);
Serial.print("ZEUS");
delay(1000);
Serial.print("AT+PIN");
delay(1000);
Serial.print("123456789");
delay(1000);
*/
//Serial.println("System Started...5");
sim.begin(9600);
delay(1000);
//Serial.println("Escribe s para enviar un SMS,w para enviar otro mensaje,p para reevisar saldo,r para recibirlo ,y c para llamar pendiente");
 Serial.flush();
  

}


void loop() {
  if(micros() >= voltageLastSample + 1000 )                                                                      /* every 0.2 milli second taking 1 reading */
          {
            voltageSampleRead = (analogRead(VoltageAnalogInputPin)- 512)+ voltageOffset1;                             /* read the sample value including offset value*/
            voltageSampleSum = voltageSampleSum + sq(voltageSampleRead) ;                                             /* accumulate total analog values for each sample readings*/
            
            voltageSampleCount = voltageSampleCount + 1;                                                              /* to move on to the next following count */
            voltageLastSample = micros() ;                                                                            /* to reset the time again so that next cycle can start again*/ 
          }
        
        if(voltageSampleCount == 1000)                                                                                /* after 4000 count or 800 milli seconds (0.8 second), do the calculation and display value*/
          {
            voltageMean = voltageSampleSum/voltageSampleCount;                                                        /* calculate average value of all sample readings taken*/
            RMSVoltageMean = (sqrt(voltageMean))*1.5;                                                                 // The value X 1.5 means the ratio towards the module amplification.      
            adjustRMSVoltageMean = RMSVoltageMean + voltageOffset2;                                                   /* square root of the average value including offset value */                                                                                                                                                       /* square root of the average value*/                                                                                                             
            FinalRMSVoltage = RMSVoltageMean + voltageOffset2;                                                        /* this is the final RMS voltage*/
            if(FinalRMSVoltage <= 2.5)                                                                                /* to eliminate any possible ghost value*/
            {FinalRMSVoltage = 0;}
            //Serial.print(" The Voltage RMS value is: ");
            Serial.print(FinalRMSVoltage);
          //  Serial.print(FinalRMSVoltage,decimalPrecision);
            Serial.println("V");
            voltageSampleSum =0;                                                                                      /* to reset accumulate sample values for the next cycle */
            voltageSampleCount=0;                                                                                     /* to reset number of sample for the next cycle */
          }
  //Serial.print(watts);
  //Serial.write(watts);
 // Serial.write("w\n");
  //watts+=10;
//delay(1000);
  /*
  if(setjmp(exception_mng)){
     Serial.println("Error");
  }
  */
  delay(10);
 if(Estado==0){
  

  //Serial.println("Electricidad Desactivada");
  Contador++;

delay(1000);
  //Serial.println(Contador);
 }
  if(Estado==1){


  if(Contador!=0){
      //Serial.println("Electricidad Activada...");
    // Serial.print("despues de ");
    // Serial.print(Contador);
     //Serial.println(" segundos");
      delay(1000);
  }
  

  Contador=0;
 // delay(1000);
 }
//  if(k==2){
   // Serial.println("regreso la luz");
   
 
    
   
  //  k=0;
 // }
   if(Contador==5){
  
  //Serial.println("Usuario-telefono ");
 //Serial.println(numbersusuarios[0]);
 //CicloPrueba();
  //delay(5000);
 CicloPrueba2();
 /*
  for(int i=0;i<=tamanoc;i++){
    //Serial.println(nombresusuarios[i]);
     Serial.println(numbersusuarios[i]);
      SendMessage2(numbersusuarios[i]);
      delay(2000);
  //Serial.println(dato[i]);

// concat1.concat(dato[i]);
 }
*/

//Serial.println(Serial.read());

  
    //CicloPrueba();
     //CicloPrueba();
  
  
  
  
  //  SendMessageInd();
    //CicloPrueba();
    //delay(4000);
  //  SendMessage();
  
   
    //k=0;
  }
  if(k==1){
   // Serial.println("entro al if");
    // CicloPrueba();
  
  
  
  
  //  SendMessageInd();
    //CicloPrueba();
    //delay(4000);
  //  SendMessage();
  
   
    k=0;
  }
  
  if(Serial.available()  >  0){
    
 //Serial.println(Serial.available());

    switch(Serial.read())
    {
   //Serial.println("entro0");
      case 'a':
      if(Serial.available()  > 0){
        
      
//Serial.write("rd\n");

//Serial.println(Serial.readString());
//Serial.println(Serial.readStringUntil('\n'));
String dato=Serial.readStringUntil('\n');
 //erial.println("111");
 //Serial.println(dato);
//int p2=Serial.read();
int p2=3;
//Serial.println(dato);
//Serial.println(Serial.read());
 for(int i=0;i<5;i++){
  //Serial.println(dato[i]);
  if(dato[i]=='1'){
    a[i]=1;
  //Serial.println(dato[i]);
}
 if(dato[i]=='0'){
    a[i]=0;
 // Serial.println(dato[i]);
}
 }

//String dispositivos=Serial.readString();
//Serial.println("disposotivos");

  // Serial.flush();
      //Serial.write("ru\n");
       Serial.flush();
     }
      break;

case 't':
      if(Serial.available()  > 0){
        
      Serial.flush();
  // Serial.write("rut\n");   

//Serial.println(Serial.readString());
//Serial.println(Serial.readStringUntil('\n'));
//String dato=Serial.readStringUntil('\n');
//tam=dato.toInt();

tamanob=0;


 //erial.println("111");
 //Serial.println(dato);
//int p2=Serial.read();

//Serial.println(Serial.read());


//String dispositivos=Serial.readString();
//Serial.println(tam);

    
       Serial.flush();
     }
      break;
      case 'q':
      if(Serial.available()  > 0){
        
      Serial.flush();
  // Serial.write("rut\n");   

//Serial.println(Serial.readString());
//Serial.println(Serial.readStringUntil('\n'));
//String dato=Serial.readStringUntil('\n');
//tam=dato.toInt();

tamanoc=0;

 //erial.println("111");
 //Serial.println(dato);
//int p2=Serial.read();

//Serial.println(Serial.read());


//String dispositivos=Serial.readString();
//Serial.println(tam);

    
       Serial.flush();
     }
      break;
//try  tal vvez?
 case 'b':
      if(Serial.available()  > 0){
        Serial.flush();
       if(tamanob>20){
        
        
 // Serial.println("se lleno");
  break;
 }



//String dato1=Serial.readStringUntil(',');

//Serial.println("seto");
//Serial.println(dato1);
 
   //Serial.write("b"); 
   //String dato1=Serial.readString();  
   String datop="prueba";
String dato1=Serial.readStringUntil('\n');
nombresusuarios[tamanob]=dato1;
//Serial.println("los datos son: "+dato1+"alv"+datop);
//Serial.println(dato1);
// SendMessage2(dato1);
Serial.flush();
/*int medio;
String numerot;
String telefonot;
String concat1;
String concat2;
for(int i=0;i<dato.length();i++){
  //Serial.println(dato[i]);
  concat1.concat(dato[i]);
  if(dato[i]==','){
   concat2=concat1;
   concat1="";
    
}
 concat1.concat(dato[i]);
 }
Serial.println("concat1");
Serial.println(concat1);
Serial.println("concat2");
Serial.println(concat2);



nombresusuarios[tamano]= concat1;
numbersusuarios[tamano]= concat2;
*/
 tamano++;
  tamanob++;





     }
    
     
      break;
      case 'c':
      if(Serial.available()  > 0){
        Serial.flush();
       if(tamanoc>20){
        
        
  Serial.println("se lleno");
  break;
 }





   //Serial.write("b");   
String dato2=Serial.readStringUntil('\n');
numbersusuarios[tamanoc]=dato2;
 // Serial.println(tamanoc);
//Serial.println(dato2);
String dato3=dato2;
 //Serial.println(numbersusuarios[tamanoc]);
/*int medio;
String numerot;
String telefonot;
String concat1;
String concat2;
for(int i=0;i<dato.length();i++){
  //Serial.println(dato[i]);
  concat1.concat(dato[i]);
  if(dato[i]==','){
   concat2=concat1;
   concat1="";
    
}
 concat1.concat(dato[i]);
 }
Serial.println("concat1");
Serial.println(concat1);
Serial.println("concat2");
Serial.println(concat2);



nombresusuarios[tamano]= concat1;
numbersusuarios[tamano]= concat2;
*/
 tamano++;

 tamanoc++;



     }
    
     
      break;
      //este bloqeu no jala
       case 'z':
       Serial.write("rd\n");
   delay(1000);
   Serial.write("ru\n");
   delay(1000);
      break;
      case 'm':
      Serial.println("System Started...5");
      
      SendMessage();
   
      break;
       case 'k':
    CicloPrueba2();
   
      break;
     /* case 'q':
     k=2;
     Estado=1;
   
      break;*/
       case '9':
     Serial.write("rd\n");
   delay(1000);
   Serial.write("ru\n");
   delay(1000);
      break;
      case 'w':
    
   Serial.println("System Started...5");

  SendMessage4(number4);
 

    
   
      break;
       case '6':
    
   Serial.println("System Started...5");

  SendMessage6(number4);
 

    
   
      break;
      case 'p':
      
   Serial.println("Porcentaje de bateria");
   Serial.println(Bateria);
   Serial.write("l\n");
      break;
      case '1':
      
      if(digitalRead(4)==HIGH){
         digitalWrite(4,0);
      }else{
        digitalWrite(4,1);
      }
      
      break;
      
       
     
       case '2':
       if(digitalRead(5)==HIGH){
         digitalWrite(5,0);
      }else{
        digitalWrite(5,1);
      }
      
      break;
      
       case '3':
       if(digitalRead(6)==HIGH){
         digitalWrite(6,0);
      }else{
        digitalWrite(6,1);
      }
      
      break;
        
       case '4':
   
      if(digitalRead(7)==HIGH){
         digitalWrite(7,0);
      }else{
        digitalWrite(7,1);
      }
      
      break;
      
       case '5':
        if(digitalRead(8)==HIGH){
         digitalWrite(8,0);
      }else{
        digitalWrite(8,1);
      }
      
      break;
    
      
    
      
      case 'y':
//      try{
  CicloPrueba();
/*
  int dif=millis();
   
    CicloPrueba();

 if(millis()-dif> 5000){
  longjmp(exception_mng, 1);
 }
 Serial.println("valio vrg");



      
  //    }
      //catch(int e){
    //     Serial.println(e);
      //  Serial.println("Fallo");
        break;
      //}*/
    
      //for(int i=0;i<5;i++){
        //SendMessage();
      //Serial.println(numbers2[i]+i);
      
    //SendMessage2(numbers2[i]);
    //delay(2000);
  //}
      //SendMessage5(number);
      
   //if(sim.available()> 0)
   // Serial.write(sim.read());
     //SendMessage3(number);
    
      
    //  SendMessage3(number2);
      //break;
      case 'r':
      ReceiveMessage();
      break;
      case 'l':
      callNumber();
      break;
       case 's':
      Saldo2();
      break;
    }

}

   
    if(sim.available()> 0)
    Serial.write(sim.read());
    
      
    
  
  // put your main code here, to run repeatedly:

}
void apagado (){
 
  digitalWrite(4,a[0]);
       digitalWrite(5,a[1]);
       digitalWrite(6,a[2]);
       digitalWrite(7,a[3]);
       digitalWrite(8,a[4]);
      
 // ReceiveMessage();
 Estado=0;
  k=1;
  //if(Serial.available()  > 0)
 // delay(2000);
//CicloPrueba();
  
   }
void encendido (){
  
      // digitalWrite(4,1);
       //digitalWrite(5,1);
      // digitalWrite(6,1);
       //digitalWrite(7,1);
       //digitalWrite(8,1);
   Estado=1;
  k=2;
  }
void CicloPrueba(){
  //Serial.println("Mandando  msj");
  for(int i=0;i<5;i++){
        //SendMessage();
     // Serial.println(numbers2[i]+i);
      
    SendMessage3(numbers2[i]);
    delay(2000);
  }



  
}
void CicloPrueba2(){
  //Serial.println("Mandando  msj");
  
  for(int i=0;i<tamanoc;i++){
        //SendMessage();
     // Serial.println(numbersusuarios[i]);
      
   // SendMessage(nombresusuarios[i],numbersusuarios[i]);
   SendMessage3(numbersusuarios[i]);
   delay(2000);
   //original
   SendMessage4(numbersusuarios[i]);
   delay(2000);
   //nombresusuarios
      //SendMessage3(numbersusuarios[i]);
   //delay(2000);
   //original
   //SendMessage6(numbersusuarios[i]);
   
  //  delay(2000);
     for(int j=0;j<5;j++){
      SendMessage7(numbersusuarios[i],j);
       delay(2000);
     }
  }
delay(10000);


  
}
void SendMessageInd(){
Serial.println("Mandando  msj");

  sim.println("AT+CMGF=1");
  delay(500);
 Serial.println("Mandando  msj2");
  sim.println("AT+CMGS=\""+number+"\"\r");
delay(500);
Serial.println("Mandando  msj3");
String SMS = "Energia electrica desactivada ";
sim.println(SMS);
delay(200);
sim.println((char)26);
delay(400);
_buffer = _readSerial();
Serial.println("Mandando  msj4");


  
}
void SendMessage(){
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+number+"\"\r");
delay(200);

String SMS = "osos ";
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();





  
}

void SendMessage2(String n,String t){
   // Serial.println("Paso el tiemnpo limite se manda mensaje de alerta");
   // Serial.print("Bateria: ");
    //Serial.print(Bateria);
    //Serial.println(" %");
   // Serial.println("Dispositivos Conectados:");
  
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+t+"\"\r");
delay(200);
 //Serial.print(n);
//String SMS = "La energia electrica ha sido desactivada! Bateria: "+Bateria+"% Dispositivos conectados: ";
  String SMS = "La energia electrica ha sido desactivada!";
//String SMS = "La energia electrica ha sido desactivada! Bateria: kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
//String SMS = "La energia electrica ha sido desactivada! Bateria: kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
 //Serial.print(SMS);
sim.println(SMS);
delay(100);
sim.println((char)26);

delay(200);
_buffer = _readSerial();




  
}
void SendMessage3(String n){
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
String SMS = "La energia electrica ha sido desactivada!";
//String SMS = "jirafas";
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();




  
}
void SendMessage4(String n){
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
//Serial.println("Bateria:"+Bateria);
String convb=String(Bateria);
String SMS = "Bateria:"+convb;
//Serial.println("Bateria:"+convb);
//String SMS = "jirafas";
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();




  
}
void SendMessage6(String n){
  String DTemp;
    for(int i=0;i<5;i++){
  // Serial.print("Enchufe");
   //Serial.print(i+1);
   DTemp+=+i+1;
   if(a[i]==0){
   // Serial.println(": Activado");
      DTemp+=") ON ";
   }
    if(a[i]==1){
          DTemp+=")OFF ";
  //  Serial.println(": Desactivado");
   }
        
  //Serial.println(dato[i]);
  

 }
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
//Serial.println(DTemp);
String SMS = String(DTemp);
//Serial.println("Dsipositivos"+String(DTemp));
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();
//Serial. flush();




  
}
void SendMessage7(String n,int K){
  String DTemp;
   
  // Serial.print("Enchufe");
   //Serial.print(i+1);
  // DTemp+=+i+1;
   DTemp+=K;
   DTemp+=") ";
    DTemp+=nombresusuarios[K];
   if(a[K]==0){
   // Serial.println(": Activado");
      DTemp+=":  ON ";
   }
    if(a[K]==1){
        DTemp+=":  OFF ";
  //  Serial.println(": Desactivado");
   }
        
  //Serial.println(dato[i]);
  

 
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
//Serial.println(DTemp);
String SMS = String(DTemp);
//Serial.println("Dsipositivos"+String(DTemp));
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();
//Serial. flush();




  
}
void SendMessage5(String n){
  sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
 

String SMS = "Energia electrica desactivada  40% de bateria restante";
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);

_buffer = _readSerial();
//Serial. flush();
 //sim.println("AT+CMGF=1");
 // delay(200);
 
  sim.println("AT+CMGS=\""+n+"\"\r");
delay(200);
 

String SMS2 = "Energia electrica desactivada  60% de bateria restante";
sim.println(SMS2);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();




  
}
void ReceiveMessage(){
Serial.println("SIM800 Read an SMS");
sim.println("AT+CMGF=1");
delay(200);
sim.println("AT+CNMI=1,2,0,0,0");
delay(200);
Serial.write("Unread message done");


  
}
String _readSerial(){
_timeout=0;
while(!sim.available()&& _timeout < 12000)
{
  delay(13);
  _timeout++;
}
if(sim.available()){
  return sim.readString();
}
}
void callNumber(){
  sim.print(F("ATD"));
   sim.print(number);

   
  

   
    sim.print(F(";\r\n"));
    _buffer = _readSerial();
    Serial.println(_buffer);

 
}

void Saldo2(){
    sim.println("AT+CMGF=1");
  delay(200);
 
  sim.println("AT+CMGS=\""+Saldo+"\"\r");
delay(200);

String SMS = "Saldo";
sim.println(SMS);
delay(100);
sim.println((char)26);
delay(200);
_buffer = _readSerial();


 
}
