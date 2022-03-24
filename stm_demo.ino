
//#include "stm32f10x_gpio.h"

//String* PortA_string[] = {PA_1,PA_2,PA_3,PA_4,PA_5,PA_6,PA_7,PA_8,PA_9,PA_10};
////int lop = 
//uint8_t k=128;

 uint8_t k = 128;
 uint8_t p = 128;

void setup() {
   
   // put your setup code here, to run once:
   //PortA_string[10] = {PA_1,PA_2,PA_3,PA_4,PA_5,PA_6,PA_7,PA_8,PA_9,PA_10};
   
   GPIO_InitTypeDef GPIO_InitStruct, GPIO_InitStruct2;
   //RCC->AHBENR = (1<<17);          //Enable PortA Clock
   
   //for (int c=1; c<2; c++)
   //pinMode(PortA_string[c], INPUT_PULLUP); 
   //asnprintf(num, "%d", n1);
   //GPIO->MODER = 0x00000000;    //Setup PortA as Input Mode

  HAL_Init();
  SystemClock_Config();
  
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; //| GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
  
  GPIO_InitStruct2.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStruct2.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct2.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //LL_GPIO_Init();

  Serial.begin(9600);
}

void loop() {
    
    /* Serial.println("eSpark");
     for (uint8_t k=1; k<11; k++)
     {
        if (digitalRead(PortA_string[0]) == LOW)
        Serial.print(k);
        Serial.println("IS PRESSED")
     }*/
     
     if(HAL_GPIO_ReadPin(GPIOA, 128) == 1) 
     {
        Serial.println("Button is not pressed");
        delay(100);
     }


     else if (HAL_GPIO_ReadPin(GPIOA, 128) == 0)
     {
        Serial.println("Button is pressed");
        delay(100);
     }

     
     //for (uint8_t k=256; k>0; k/2)
     while (k > 0)
     {
            if (HAL_GPIO_ReadPin(GPIOA, k) == 0)
            {
                Serial.print("MESSAGE_");
                Serial.println(k);
                delay(200);

                /*p = k/2;

                  while (p > 1)
                  {
                    if (HAL_GPIO_ReadPin(GPIOA, p) == 0)
                    Serial.print("NULL");

                    p = p/2;

                    if (p == 1)
                    {
                      if (HAL_GPIO_ReadPin(GPIOA, p) == 0)
                      Serial.print("NULL");
                    }
                  }
                }*/
                
                //while (HAL_GPIO_ReadPin(GPIOA, k) )
            
            p=k/2;  
            
            while (p > 0)
              {
                 if (HAL_GPIO_ReadPin(GPIOA, p) == 0)
                 {
                  Serial.print("MESSAGE_");
                  Serial.println("LOW_PRIORITY_");
                  Serial.println(p);
                  delay(100);
  
                  p = p/2;
                 }

                 else {
                  Serial.print("MESSAGE_");
                  Serial.println("NULL_");
                  Serial.println(p);
                  delay(100);
                  
                  p = p/2;
                 }
            }
            }
            else if (HAL_GPIO_ReadPin(GPIOA, k) == 1)
            {
                Serial.print("MESSAGE_NOT_PRESS");
                Serial.println(k);
                delay(200);
            }

            /*for (p=k/2; p>0;)
            {
              if (HAL_GPIO_ReadPin(GPIOA, p) == 0)
              {
                Serial.print("MESSAGE_");
                Serial.println("NULL");
                delay(300);

                p = p/2;

                if (p==1)
                p=0;
              }
            }*/
            
            k = k/2;

            //if (k==1)
            //k=0;  
      }
   //p=128;
}
