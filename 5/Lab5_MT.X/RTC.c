#include <xc.h>
#include "I2C.h"
#include "RTC.h"

/*int  BCD_2_DEC(int to_convert)
{
   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

int DEC_2_BCD (int to_convert)
{
   return ((to_convert / 10) << 4) + (to_convert % 10);
}

void Config_Time_Date(void)
{
   I2C_Master_Start();       
   I2C_Master_Write(0xD0); 
   I2C_Master_Write(0);  
   I2C_Master_Write(DEC_2_BCD(sec)); //update sec
   I2C_Master_Write(DEC_2_BCD(min)); //update min
   I2C_Master_Write(DEC_2_BCD(hour)); //update hour
   I2C_Master_Write(1); //ignore updating day
   I2C_Master_Write(DEC_2_BCD(date)); //update date
   I2C_Master_Write(DEC_2_BCD(month)); //update month
   I2C_Master_Write(DEC_2_BCD(year)); //update year
   I2C_Master_Stop();
}

void Update_Current_Date_Time(void)
{
   //START to Read
   I2C_Master_Start();       
   I2C_Master_Write(0xD0); 
   I2C_Master_Write(0);    
   I2C_Master_Stop(); 
   
  //READ
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   sec = BCD_2_DEC(I2C_Master_Read(0));    
   min = BCD_2_DEC(I2C_Master_Read(0));   // Read sec from register 
   hour = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Read(0);
   date = BCD_2_DEC(I2C_Master_Read(0));  
   month = BCD_2_DEC(I2C_Master_Read(0));  
   year = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
    
  //END Reading  
    I2C_Master_Start();
    I2C_Master_Write(0xD1);                              // Initialize data read
    I2C_Master_Read(0);    
    I2C_Master_Stop(); 

}
*/