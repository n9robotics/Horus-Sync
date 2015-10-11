//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// N9 Robotics
//
// AUTOR:
// Luis Enrique Braga Ramirez
// 2015
//
// PROYECTO:
// Horus-Sync (sincronización hemisférica) 
//
// COMPONENTES:
//
// 1 - Placa Arduino (Mega)
//
// 2 - diodos RGB
// Pines
// r-gdn-g-b (gnd = pata larga)
// 
// 7 resistencias 220 homs 
//
// 1 Potenciometro 10k homs
// 
// 4 micro botones pulsadores 
//
// 1 Fuente 12 vcd 500 ma  jack centro + exterior -
//
// TEORIA:
// Si el oído(ojo) izquierdo recibe sonidos(luz) con una frecuencia de 40 Hz y el oído(ojo) derecho de 50 Hz, el pulso binaural resultante será de 10 Hz

// En neurociencia, hay cinco frecuencias de ondas cerebrales distintas
// Gamma 40 -> ? hz    - introspección
// Beta 14 -> 40 hz    - estado normal
// Alfa 7.5 -> 14 hz   - relajacion profunda
// Theta 4 -> 7.5 hz   - meditacion  y sueño ligero
// Delta 0.5 -> 4 hz   - sueño profundo y meditacion tracendental
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include <LiquidCrystal.h>

//Pines del lcd JHD 162A
LiquidCrystal lcd(42,44,46,48,50,52);

// JHD 162A
// 1_ 2_ 3_ 4_ 5_ 6_ 7_ 8_ 9_ 10_ 11_ 12_ 13_ 14_ 15_ 16_

// 1  Vss              -> GND
// 2  Vcc              -> +5v
// 3  VEE              -> Potenciometro
// 4  RS               -> 42 
// 5  R/W              -> GND 
// 6  E                -> 44 
// 7  DB0              ->  
// 8  DB1              ->  
// 9  DB2              ->  
// 10 DB3              ->  
// 11 DB4              -> 46  
// 12 DB5              -> 48  
// 13 DB6              -> 50 
// 14 DB7              -> 52 
// 15  +  - Backlight  -> 5V
// 16 GND - Backlight  -> GND

//Pines PWM para poder controlar led RGB

//Led IZQ
#define Pin_R1 2
#define Pin_G1 3
#define Pin_B1 4

//Led DER             
#define Pin_R2 5
#define Pin_G2 6
#define Pin_B2 7

//Pines para Pulsadores (Pad)
#define Pin_Boton_Arriba 38
#define Pin_Boton_Abajo 36 
#define Pin_Boton_Izquierda 34
#define Pin_Boton_Derecha 32

//variables para switch 
int Boton_Arriba = 0;
int Boton_Abajo =0;
int Boton_Izquierda =0;
int Boton_Derecha =0;

//Color RGB Izq
byte R_Led_Izq=0;
byte G_Led_Izq=0;
byte B_Led_Izq=0;

//Color RGB Der
byte R_Led_Der=0;
byte G_Led_Der=0;
byte B_Led_Der=0;

//variables para switch  - Pulsos
int Led_Izq_0n=0;
int Led_Der_0n=0;

//Timers
long Milisegundos_Led_Izq=0;
long Milisegundos_Led_Der=0;

long Milisegundos_Menu=0;
long Milisegundos_LCD=0;
long Milisegundos_Cursor=0;
long Milisegundos_Logo=0;


int Frecuencia=0;
float Frecuencia_Base=0;


//>>>>>>>>>>>>>>>>>>>>>>>>
int indice_Cursor = 0;

String Cursor[] = {  
  "<", 
  " " 
};

//>>>>>>>>>>>>>>>>>>>>>>>>
// total -1
int indice_menu = 0;
int indice_max  = 2;

//numero de opccion
String Menu_Numero[] = {  
  "1", 
  "2",
  "3"
};

//nombre de las opciones
String Menu_Opccion[] = {  
  "RGB", 
  "HZ", 
  "Base" 
};

//sub opciones - variables de control
int Opccion_Seleccion[] = {  
  0, //RGB
  0, //HZ
  0  //Base
};
 
//topes de sub opciones
int Opccion_Max[] = {  
  7, //RGB
  40,//HZ
  7  //Base
};
 
String Opccion_A[] = {  
  "Apagado ",//0
  "Rojo    ",//1
  "Verde   ",//2
  "Azul    ",//3
  "Cian    ",//4
  "Violeta ",//5 
  "Morado  ",//6 
  "Amarillo" //7
};

String Opccion_B[] = {  
  "0 Nulo  ",
  "1 Delta ",
  "2 Delta ",
  "3 Delta ", 
  "4 Delta ", 
  "5 Theta ", 
  "6 Theta ", 
  "7 Theta ", 
  "8 Alfa  ", 
  "9 Alfa  ", 
  "10 Alfa ", 
  "11 Alfa ", 
  "12 Alfa ", 
  "13 Alfa ", 
  "14 Alfa ", 
  "15 Beta ", 
  "16 Beta ", 
  "17 Beta ", 
  "18 Beta ", 
  "19 Beta ", 
  "20 Beta ", 
  "21 Beta ", 
  "22 Beta ", 
  "23 Beta ", 
  "24 Beta ", 
  "25 Beta ", 
  "26 Beta ", 
  "27 Beta ", 
  "28 Beta ", 
  "29 Beta ", 
  "30 Beta ", 
  "31 Beta ", 
  "32 Beta ", 
  "33 Beta ", 
  "34 Beta ", 
  "35 Beta ", 
  "36 Beta ", 
  "37 Beta ", 
  "38 Beta ", 
  "39 Beta ", 
  "40 Gamma" 
};

String Opccion_C[] = {  
  "Fija    ",//0
  "1 HZ    ",//1
  "5 HZ    ",//2
  "10 HZ   ",//3
  "15 HZ   ",//4
  "20 HZ   ",//5 
  "25 HZ   ",//6 
  "30 HZ   " //7 
};

//>>>>>>>>>>>>>>>>>>>>>>>>
int indice_Animacion = 0;
String Logo_Animacion[] = {  
  "  N9 Robotics   ", 
  "                                                                                    " 
 };

//>>>>>>>>>>>>>>
void setup(){
  
   //Numero de caracteres y filas del LCD JHD 162A
   lcd.begin(16, 2);
  
   //Led IZQ
   pinMode(Pin_R1 , OUTPUT ); 
   pinMode(Pin_G1 , OUTPUT ); 
   pinMode(Pin_B1 , OUTPUT ); 

   //Led DER
   pinMode(Pin_R2 , OUTPUT ); 
   pinMode(Pin_G2 , OUTPUT ); 
   pinMode(Pin_B2 , OUTPUT ); 
   
   //Pulsadores
   pinMode(Pin_Boton_Arriba , INPUT ); 
   pinMode(Pin_Boton_Abajo , INPUT ); 
   pinMode(Pin_Boton_Izquierda , INPUT ); 
   pinMode( Pin_Boton_Derecha , INPUT ); 
   
   //Contadores
   Milisegundos_Menu = millis();
   Milisegundos_LCD = Milisegundos_Menu;
   Milisegundos_Cursor = Milisegundos_Menu;
   Milisegundos_Logo =  Milisegundos_Menu;
   
   Milisegundos_Led_Izq=Milisegundos_Menu;
   Milisegundos_Led_Der=Milisegundos_Menu;     

   //dibuja el interfas por primera ocacion
   Pantalla();
}



//>>>>>>>>>>>>>>
void loop() {
  //botones del menu
  Menu_Pad();
  
  //refreco pantalla
  Pantalla();
  
  Leds_HZ();
  Leds_Color();
}


//>>>>>>>>>>>>>>
void Menu_Pad(){

    //1000/100 = 10
    if( millis()-Milisegundos_Menu>=10){
    
       int Barr = digitalRead(Pin_Boton_Arriba);
       if(Barr==HIGH){ 
           
         if(Boton_Arriba==0){
             Boton_Arriba=1;
             indice_menu=indice_menu-1;
             if(indice_menu<0)
             {
               indice_menu=indice_max;//wrap
             } 
           
            }
            
       }else{
         Boton_Arriba=0;
       }

        int Babj = digitalRead(Pin_Boton_Abajo); 
         if(Babj==HIGH){ 
            
           if(Boton_Abajo==0){
              Boton_Abajo=1;
              indice_menu=indice_menu+1; 
              if(indice_menu>indice_max)
              {
               indice_menu=0;
              } 
            }
            
         }else{
           Boton_Abajo=0;
         }
         
        int Bizq = digitalRead(Pin_Boton_Izquierda); 
        if(Bizq==HIGH){  
          
           if(Boton_Izquierda==0){
              Boton_Izquierda=1;
                   Opccion_Seleccion[indice_menu] = Opccion_Seleccion[indice_menu]+1;
                if(Opccion_Seleccion[indice_menu]>Opccion_Max[indice_menu])
                {
                   Opccion_Seleccion[indice_menu]=0;
                } 
              } 
              
        }else{
           Boton_Izquierda=0;
        }
           
        int Bder = digitalRead(Pin_Boton_Derecha); 
        if(Bder==HIGH){  
          
           if(Boton_Derecha==0){
              Boton_Derecha=1;
                   Opccion_Seleccion[indice_menu] = Opccion_Seleccion[indice_menu]-1;
                if(Opccion_Seleccion[indice_menu]<0)
                {
                   Opccion_Seleccion[indice_menu]=Opccion_Max[indice_menu];
                } 
              } 
              
        }else{
           Boton_Derecha=0;
        }
           
       //Reset
       Milisegundos_Menu=millis();
    }
  
}


//>>>>>>>>>>>>>>
void Pantalla(){
  
  //refresco de la pantalla  1000/60 = 16.666
 if( millis()-Milisegundos_LCD>=16){

// no es necesario limpiar la pantalla - esto causa fliquer 
//   lcd.clear();

     lcd.setCursor(0, 0);

     switch (indice_menu) {

       //rgb
       case 0:    
        lcd.print(Menu_Numero[indice_menu]+Cursor[indice_Cursor]+" "+Menu_Opccion[indice_menu]+" :"+ Opccion_A[ Opccion_Seleccion[indice_menu] ] );
       break;

       //hz
       case 1:    
        lcd.print(Menu_Numero[indice_menu]+Cursor[indice_Cursor]+" "+Menu_Opccion[indice_menu]+" :"+ Opccion_B[ Opccion_Seleccion[indice_menu] ] );
       break;

       //Base
       case 2:    
        lcd.print(Menu_Numero[indice_menu]+Cursor[indice_Cursor]+" "+Menu_Opccion[indice_menu]+" :"+ Opccion_C[ Opccion_Seleccion[indice_menu] ] );
       break;
     }

     //logo     
     lcd.setCursor(0, 1);
     lcd.print(" "+Logo_Animacion[indice_Animacion] );
          
    //Reset
    Milisegundos_LCD=millis();
  }
  
  
  //refreco cursor  1000/4 = 250
  if( millis()-Milisegundos_Cursor>=250){
     
      indice_Cursor=indice_Cursor+1;
      if(indice_Cursor>1)
      {
       indice_Cursor=0;
      }
      
    //Reset
    Milisegundos_Cursor=millis();
  }
  
  //refreco animacion  1000/2 = 500
  if( millis()-Milisegundos_Logo>=500){
  
     // indice_Animacion = indice_Animacion +1 ;
        indice_Animacion = 0;
      if(indice_Animacion>1)
      {
       indice_Animacion=0;
      }
  
    //Reset
    Milisegundos_Logo=millis();
  }
  
  
  
}


//-------------------------------------
void Led_IZQ_RGB() { 
  analogWrite( Pin_R1 , R_Led_Izq);
  analogWrite( Pin_G1 , G_Led_Izq);
  analogWrite( Pin_B1 , B_Led_Izq); 
}

void Led_IZQ_Negro() { 
  analogWrite( Pin_R1 , 0);
  analogWrite( Pin_G1 , 0);
  analogWrite( Pin_B1 , 0); 
}

//-------------------------------------
void Led_DER_RGB() { 
  analogWrite( Pin_R2 , R_Led_Der);
  analogWrite( Pin_G2 , G_Led_Der);
  analogWrite( Pin_B2 , B_Led_Der); 
}

void Led_DER_Negro() { 
  analogWrite( Pin_R2 , 0);
  analogWrite( Pin_G2 , 0);
  analogWrite( Pin_B2 , 0); 
}

//-------------------------------------
void Reset_Leds_Timers() { 
  Milisegundos_Led_Izq=millis();
  Milisegundos_Led_Der=Milisegundos_Led_Izq;
}


void Leds_HZ(){

  //Selecion de Base 
  if(indice_menu==2)
  {
     switch ( Opccion_Seleccion[indice_menu]) {
        case 0://Fija
          Frecuencia_Base = 0;
        break;

        case 1://1 HZ
          Frecuencia_Base = 1;
        break;

        case 2://5 HZ
          Frecuencia_Base = 5;
        break;

        case 3://10 HZ
          Frecuencia_Base = 10;
        break;

        case 4://15 HZ
          Frecuencia_Base = 15;
        break;

        case 5://20 HZ
          Frecuencia_Base = 20;
        break;

        case 6://25 HZ
          Frecuencia_Base = 25;
        break;

        case 7://30 HZ
          Frecuencia_Base = 30;
        break;
     }    
       
  }
  
  if(Frecuencia_Base>0)
  {
     //hojos    
     Led_IZQ(1000/Frecuencia_Base);
    
     int Base = Frecuencia_Base+Opccion_Seleccion[1];
     Led_DER(1000/Base );

  }else //0 = Fija
  {
     Led_IZQ_RGB();
     Led_DER_RGB();
  }
    
}



//>>>>>>>>>>>>>>
void Led_IZQ( int Retardo){

    if( millis()- Milisegundos_Led_Izq>=Retardo ){
    
       //switch on off
       Led_Izq_0n = 1 - Led_Izq_0n;
      
       if(Led_Izq_0n==1){  
         Led_IZQ_RGB();
       }else
       {
         Led_IZQ_Negro(); 
       }
       //Reset
        Milisegundos_Led_Izq=millis();
    }
  
}

//>>>>>>>>>>>>>>
void Led_DER( int Retardo){

    if( millis()- Milisegundos_Led_Der>=Retardo ){
    
       //switch on off
       Led_Der_0n = 1 - Led_Der_0n;
      
       if(Led_Der_0n==1){  
          Led_DER_RGB();
       }else
       {
         Led_DER_Negro(); 
       }
       
       //Reset
       Milisegundos_Led_Der=millis();
    }
  
}


void Leds_Color() { 

  //RGB 
  if(indice_menu==0)
  {
  
   switch (Opccion_Seleccion[indice_menu]) {
      
       case 0://apagado    
          R_Led_Izq=0;
          G_Led_Izq=0;
          B_Led_Izq=0;
          
          R_Led_Der =0;
          G_Led_Der =0;
          B_Led_Der =0;          
       break;
   
       case 1://rojo    
          R_Led_Izq=255;
          G_Led_Izq=0;
          B_Led_Izq=0;
          
          R_Led_Der =255;
          G_Led_Der =0;
          B_Led_Der =0;          
       break;
    
       case 2://verde    
          R_Led_Izq=0;
          G_Led_Izq=255;
          B_Led_Izq=0;
          
          R_Led_Der =0;
          G_Led_Der =255;
          B_Led_Der =0;          
       break;

       case 3://azul    
          R_Led_Izq=0;
          G_Led_Izq=0;
          B_Led_Izq=255;
          
          R_Led_Der =0;
          G_Led_Der =0;
          B_Led_Der =255;          
       break;

       case 4://cian    
          R_Led_Izq=0;
          G_Led_Izq=210;
          B_Led_Izq=255;
          
          R_Led_Der =0;
          G_Led_Der =210;
          B_Led_Der =255;          
       break;

       case 5://violeta    
          R_Led_Izq=164;
          G_Led_Izq=0;
          B_Led_Izq=255;
          
          R_Led_Der =164;
          G_Led_Der =0;
          B_Led_Der =255;          
       break;

       case 6://morado    
          R_Led_Izq=60;
          G_Led_Izq=60;
          B_Led_Izq=200;
          
          R_Led_Der =60;
          G_Led_Der =60;
          B_Led_Der =200;          
       break;

       case 7://Amarillo    
          R_Led_Izq=160;
          G_Led_Izq=255;
          B_Led_Izq=0;
          
          R_Led_Der =160;
          G_Led_Der =255;
          B_Led_Der =0;          
       break;
     }
    }
}







