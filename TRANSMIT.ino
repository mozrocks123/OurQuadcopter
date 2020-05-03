 #include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>



#include <SPI.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(7, 8);

struct Data_to_be_sent {
  float Array[5]; 
};

Data_to_be_sent sent_data;


void setup()
{
Serial.begin(9600);
radio.begin();
radio.setAutoAck(false);
radio.setDataRate(RF24_250KBPS);
radio.openWritingPipe(my_radio_pipe);  
}

void loop()
{
  
   if(Serial.available()>0)
   {
    //sent_data.Array[1] = Serial.parseFloat();
    if(Serial.read()==99 || Serial.read()==67)
    {
      Serial.println("kp: ");
      while(Serial.available()==0){radio.write(&sent_data, sizeof(Data_to_be_sent));}
      sent_data.Array[0] = Serial.parseFloat();
      
      Serial.println("kd: ");
      while(Serial.available()==0){radio.write(&sent_data, sizeof(Data_to_be_sent));}
      sent_data.Array[1] = Serial.parseFloat();
      
      Serial.println("ki: ");
      while(Serial.available()==0){radio.write(&sent_data, sizeof(Data_to_be_sent));}
      sent_data.Array[2] = Serial.parseFloat();
      
     Serial.println("Throttle increase right: ");
      while(Serial.available()==0){radio.write(&sent_data, sizeof(Data_to_be_sent));}
      sent_data.Array[3] = Serial.parseFloat();

      Serial.println("Throttle increase left: ");
      while(Serial.available()==0){radio.write(&sent_data, sizeof(Data_to_be_sent));}
      sent_data.Array[4] = Serial.parseFloat();
    
      radio.write(&sent_data, sizeof(Data_to_be_sent));

   }

   else
   {
    Serial.println("Invalid command! Please enter again");
   }
   }
    

   else
   {
    radio.write(&sent_data, sizeof(Data_to_be_sent));
    for(int i = 0; i<3; i++)
    {
      if(i == 0)
      {
    Serial.print("Sending kp: ");
    Serial.println(sent_data.Array[i]);
      }

      else if(i == 1)
      {
    Serial.print("Sending kd: ");
    Serial.println(sent_data.Array[i]);
      }

      else
      {
    Serial.print("Sending ki: ");
    Serial.println(sent_data.Array[i]);
      }
      
    }

    for(int j = 3; j<5; j++)
    {
    if(j == 3)
    {
    Serial.print("Throttle increase right: ");
    Serial.println(sent_data.Array[j]);
    //delay(500);
    }

    else
    {
    Serial.print("Throttle increase left: ");
    Serial.println(sent_data.Array[j]);
    }
    }
    
    }
   
}
 
  
  /*  sent_data.ch1=new_data;
    radio.write(&sent_data, sizeof(Data_to_be_sent));
    Serial.print("Sending: ");
    Serial.println(sent_data.ch1);

  */
