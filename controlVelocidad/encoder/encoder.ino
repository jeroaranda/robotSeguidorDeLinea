#include <ros.h>
#include <std_msgs/String.h>
ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "Hello world!";


volatile unsigned int pulse;
#include <Servo.h>
Servo myservo;
char mensaje;

void setup() {
  // setup de ros con xbee
   nh.initNode();
  nh.advertise(chatter);
    
    cli();//stop interrupts
     //set timer1 interrupt at 1Hz
    TCCR5A = 0;// set entire TCCR1A register to 0
    TCCR5B = 0;// same for TCCR1B
    TCNT5  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR5A = 6250;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR5B |= (1 << WGM52);
    // Set CS10 and CS12 bits for 256 prescaler
    TCCR5B |= (1 << CS52);  
    // enable timer compare interrupt
    TIMSK5 |= (1 << OCIE5A);
    
    //El servo se ancla al pin 11.
  myservo.attach(11); 
  
  //pines que controlan al motor.
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  //pines del lector de linea.
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  //pin del encoder
  pinMode(19,INPUT);
  //se incluyen las interrupciones.  
  attachInterrupt(4,count_pulse,FALLING);
  interrupts();
  //el motor se arranca
  digitalWrite(10,HIGH);
  analogWrite(8,100);
  sei();//allow interrupts
}

void loop() {
  
 
  nh.spinOnce();
}

void count_pulse(){
  pulse++;
}

ISR(TIMER5_COMPA_vect){
  String msj="";
  int aux;
  msj=String(digitalRead(6));
  msj+=String(digitalRead(7));
  if(myservo.read()<10)
    msj+="0";
  if(myservo.read()<100)
    msj+="0";
  msj+=String(myservo.read());
  aux=pulse*300/16;
  if(aux<10)
    msj+="0";
  msj+=String(aux);
  
  
  
  
  char mensaje[msj.length() + 1];
  msj.toCharArray(mensaje,msj.length()+1);
  
  
  
  //Se publica en chatter.
  str_msg.data = mensaje;
  chatter.publish( &str_msg );
   pulse=0;  
}

