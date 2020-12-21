/////////////////////////////Control Motor Paso a Paso ////////////////////////////////////
/////////////////////// Creado por Alejandro Quevedo Castro ////////////////////////////////////
///////////// Uso exclusivo de Comisión Chilena de Energía Nuclear ////////////////////////

                      ///////////// Relación de Giro ///////////////////
                      
                          ///////// 1 Vuelta = 200 //////////////////
                          ///////// 2 Vuelta = 400 //////////////////
                          ///////// 4 Vuelta = 800 //////////////////
                          ///////// 8 Vuelta = 1600 /////////////////
                          ///////// 16 Vuelta = 3200 ////////////////
                          ///////// 32 Vuelta = 5400 ////////////////
                      
int dir1 = 8;         // DIR-(DIR) MOTOR TRANSVERSAL 
int paso1 = 7;        // PUL-(PUL) MOTOR TRANSVERSAL  
int enable1 = 6;      // ENA-(ENA) MOTOR TRANSVERSAL 
int dir2 = 10;        // DIR-(DIR) MOTOR LONGITUDINAL
int paso2 = 11;       // PUL-(PUL) MOTOR LONGITUDINAL  
int enable2 = 9;      // ENA-(ENA) MOTOR LONGITUDINAL
int i = 0;            // Cantidad de movimiento 
int j ;
int opcion;           // Opcion, de movimiento (a = Derecha, b = Izquierda)
int carrera = 12;     // Asignación de salida para control de termino de carrera MOTOR TRANSVERSAL 
int carrera2 = 13;    // Asignación de salida para control de termino de carrera MOTOR LONGITUDINAL 
int fin = HIGH ;      // Estado de termino de carrera
int on2 = HIGH ;      // Estado de termino de carrera
int l ;               // indice de error de termino de carrera
int buttonPin = 5;    // Pin conexión boton  
int buttonPin2 = 4;   // Pin conexión boton
int buttonPin3 = 3;   // Pin conexión boton  
int buttonPin4 = 2;   // Pin conexión boton  
int buttonState = 0;  // Estado del boton    
int buttonState2 = 0; // Estado del boton
int buttonState3 = 0; // Estado del boton    
int buttonState4 = 0; // Estado del boton
int estado = A0;      // Estado de posicion
int estado2 = A1;     // Estado de posición
int posicionEstado = 0;   //Posicion de estado 1
int posicionEstado2 = 0;   //Posicion de estado 2




void setup() {
 Serial.begin (9600);
 pinMode (dir1, OUTPUT);      //  SALIDA DE LA DIRECCIÓN (TRANSVERSAL)
 pinMode (paso1, OUTPUT);     //  SALIDA PULL (TRANSVERSAL)
 pinMode (enable1, OUTPUT);   //  SALIDA ENABLE (TRANSVERSAL)
 pinMode (dir2, OUTPUT);      //  SALIDA DE LA DIRECCIÓN (LONGITUDINAL)
 pinMode (paso2, OUTPUT);     //  SALIDA PULL (LONGITUDINAL)
 pinMode (enable2, OUTPUT);   //  SALIDA ENABLE (LONGITUDINAL)
 pinMode (carrera, INPUT);    //  FIN DE CARRERA MOTOR TRANSVERSAL
 pinMode (carrera2, INPUT);   //  FIN DE CARRERA MOTOR LONGITUDINAL 
 pinMode (buttonPin, INPUT);  //  SALIDA ESTADO BOTON 1
 pinMode (buttonPin2, INPUT); //  SALIDA ESTADO BOTON 2
 pinMode (buttonPin3, INPUT); //  SALIDA ESTADO BOTON 3
 pinMode (buttonPin4, INPUT); //  SALIDA ESTADO BOTON 4
 pinMode (estado, INPUT);     //  SALIDA ESTADO MANUAL / AUTOMATICO 
 pinMode (estado2, INPUT);    //  SALIDA ESTADO MANUAL / AUTOMATICO 
 digitalWrite(enable1, HIGH); //  ESTADO DE ENABLE MOTOR TRANSVERSAL
 digitalWrite(enable2, HIGH); //  ESTADO DE ENABLE MOTOR LONGITUDINAL

  

///////////////////////////////// CALIBRACIÓN /////////////////////////////////////////

calibracion() ;
     
}

void loop() {

  posicionEstado = digitalRead (estado);
  posicionEstado2 = digitalRead (estado2);


 if (posicionEstado == HIGH){

/////////////////////////////////////////////////// CONTROL MANUAL //////////////////////////////////////////////////////////
/////////////////////////////////////////////////// MOVIMIENTO MOTOR 1 /////////////////////////////////////////////////////////

     buttonState = digitalRead(buttonPin);
     buttonState2 = digitalRead(buttonPin2);   
     buttonState3 = digitalRead(buttonPin3);
     buttonState4 = digitalRead(buttonPin4);   

    if (buttonState == HIGH){
      digitalWrite (dir1, LOW);     // Movimiento hacia la Derecha (LOW = DERECHA ; HIGH = IZQUIERA) 
      digitalWrite (paso1, HIGH);
      delay (5);
      digitalWrite (paso1, LOW);
      delay (5);
  
    }

  if (buttonState2 == HIGH){
      digitalWrite (dir1, HIGH);       //Movimiento hacia la Izquierda (LOW = DERECHA ; HIGH = IZQUIERA) 
      digitalWrite (paso1, HIGH);
      delay (5);
      digitalWrite (paso1, LOW);
      delay (5);  
    }
    

/////////////////////////////////////////////////// MOVIMIENTO MOTOR 2 ////////////////////////////////////////////////////
 
  if (buttonState3 == HIGH){
     digitalWrite (dir2, LOW);       //Movimiento hacia la Derecha (LOW = DERECHA ; HIGH = IZQUIERA) 
     digitalWrite (paso2, HIGH);
     delay (5);
     digitalWrite (paso2, LOW);
     delay (5);
    } 
    
  if (buttonState4 == HIGH){

    digitalWrite (dir2, HIGH);       //Movimiento hacia la Izquierda (LOW = DERECHA ; HIGH = IZQUIERA) 
    digitalWrite (paso2, HIGH);
    delay (5);
    digitalWrite (paso2, LOW);
    delay (5);
    }
  
  j = 0;
  }
  
/////////////////////////////////////////////////// MOVIMIENTO AUTOMATICO /////////////////////////////////////////////////

    else if (posicionEstado2 == HIGH){
      
      if (j == 0 ){
       
          calibracion();
          j = j + 1 ;
     
      }
    
    
    Serial.println ("Control Automatico");
      
    }

 
}


/////////////////////////////////////////////// VOID CALIBRACION ////////////////////////////////////////////////////////////
void calibracion (){
  delay (500);
  Serial.println ("Inicio de Calibración");
  digitalWrite (dir1, LOW);
  l = 0 ;
  while (fin == HIGH || l <= 30){
  fin = digitalRead (carrera);
  if(fin == LOW ){
  l = l + 1;
  Serial.println (l);
  }
  digitalWrite (paso1, HIGH);
  delay (5);
  digitalWrite (paso1, LOW);
  delay (5);    
  } 
  Serial.println ("MOTOR TRANSVERSAL CALIBRADO");
  delay(1000);
  digitalWrite (dir2, LOW);
  l = 0;   
  while (on2 == HIGH || l <= 30 ){
  on2 = digitalRead (carrera2);
  if(on2 == LOW){
  l = l + 1;
  Serial.println (l);
  }
  digitalWrite (paso2, HIGH);
  delay (5);
  digitalWrite (paso2, LOW);
  delay (5);    
  }
  Serial.println ("MOTOR LONGITUDINAL CALIBRADO");
  delay(500);
  Serial.println ("CALIBRACIÓN TERMINADA");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
