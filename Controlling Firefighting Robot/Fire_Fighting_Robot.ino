
/*************************************************************** 
 *  Project: $(Fire Fighting Robot) 
 *************************************************************** 
 *  $Author: Kirellos Emad Samir $ 
  *************************************************************** 
 * 
 *  Copyright 2022 by Reserve Officer College 
 * 
 ***************************************************************/   


//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 58 bytes
  { 255,5,0,0,0,51,0,16,24,0,3,3,85,21,8,22,16,26,1,0,
  39,19,12,12,16,8,70,0,1,0,48,28,12,12,16,24,82,0,1,0,
  31,29,12,12,16,8,76,0,1,0,40,38,12,12,16,24,66,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 
  uint8_t button_4; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


//           Directions Of PINS        //

#define lm1 A1 //lm1=left motor 1
#define lm2 A2
#define rm1 A3 //rm1=right motor 1
#define rm2 A4
#define br1 6 //Ba4bore  motor 
#define br2 7
#define sr  8
#define fan 12


 
/////////////////////////////////////////////
//           Status Of PINS        //
/////////////////////////////////////////////
void setup() 
{
  RemoteXY_Init ();
  pinMode(lm1,OUTPUT);   // Main Motors
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  
  pinMode(br1,OUTPUT);    // Bashboree Motor
  pinMode(br2,OUTPUT);

  pinMode(sr,OUTPUT);    // Siren
  pinMode(fan,OUTPUT);    // fan

 
}

void loop() 
{ 
  RemoteXY_Handler ();
  fan_on();
  
/////////////////////////////////////////////
//     Selector == A   "Direction Mode     //
/////////////////////////////////////////////

  if (RemoteXY.select_1==0)
  {
    if (RemoteXY.button_1==1)
    { 
    forward();
    }
    else if (RemoteXY.button_2==1)
    {
    left();  
    }
    else if(RemoteXY.button_3==1) 
   {
    right();
    }
    else if (RemoteXY.button_4==1) 
    {
      backward();
      }

      else 
    {
    stopp();
    }
 }

/////////////////////////////////////////////
//Selector == B   bashboree and siren Mode//
/////////////////////////////////////////////


 else if (RemoteXY.select_1==1)
{
  if (RemoteXY.button_1==1)
  { 
  bashboree_up();
  }
   else if (RemoteXY.button_4==1)
  {
  bashboree_down();  
  }
  else if (RemoteXY.button_2==1)
  {
  siren_on();
    
  }
else 
    {
    stopp();
    }
}

/////////////////////////////////////////////
//     Selector == c      Emergency Mode   //
/////////////////////////////////////////////

else if (RemoteXY.select_1==2)
{
stopp();
}
}






                                        
/////////////////////////////////////////////
//           Functions              //
/////////////////////////////////////////////
void forward()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

void backward()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}

void left()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

void right()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}

void stopp()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, HIGH);
  digitalWrite(br1, HIGH);
  digitalWrite(br2, HIGH);
  digitalWrite(sr, HIGH);
}
void bashboree_up()
{
  digitalWrite(br1, HIGH);
  digitalWrite(br2, LOW);
}
void bashboree_down()
{
  digitalWrite(br2, HIGH);
  digitalWrite(br1, LOW);
}

void siren_on()
{
  digitalWrite(sr, LOW);
}
void siren_off()
{
  digitalWrite(sr, HIGH);
}

void fan_on()
{
  digitalWrite(fan, HIGH);
}
  
