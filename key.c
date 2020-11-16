#include "key.h"

void key_Init(void){
	
    gpio_init(E8, GPO, 1);   //key1
    gpio_init(E3, GPO, 1);   //key2
    gpio_init(E4, GPO, 1);   //key3
    gpio_init(E5, GPO, 1);  //key4
    gpio_init(E12, GPO, 1);  //key5
    gpio_init(E28, GPO, 1);  //key6
    
}

uint8 key_scan_key1(uint8 mode){
    
	static uint8 key_up1 = 1;
    
	if(mode == 1)  
		key_up1 = 1;
    
	if(key_up1 == 1 && key1 == 0){
		systick_delay_ms(10);
		key_up1 = 0;
		if(key1 == 0) 
            return 1;
	}
    
	else if(key1 == 1 && key_up1 == 0)
		key_up1 = 1;
    
	return 0;
}

uint8 key_scan_key2(uint8 mode){
    
	static uint8 key_up2 = 1;
    
	if(mode == 1)
		key_up2 = 1;
    
	if(key_up2 == 1 && key2 == 0){
		systick_delay_ms(10);
		key_up2 = 0;
		if(key2 == 0) 
            return 1;
	}
    
	else if(key2 == 1 && key_up2 == 0)
		key_up2 = 1;
    
	return 0;
}

uint8 key_scan_key3(uint8 mode){
    
	static uint8 key_up3 = 1;
    
	if(mode == 1)
		key_up3 = 1;
    
	if(key_up3 == 1 && key3 == 0){
		systick_delay_ms(10);
		key_up3 = 0;
		if(key3 == 0) 
            return 1;
	}
    
	else if(key3 == 1 && key_up3 == 0)
		key_up3 = 1;
    
	return 0;
}

uint8 key_scan_key4(uint8 mode){
    
	static uint8 key_up4 = 1;
    
	if(mode == 1)
		key_up4 = 1;
    
	if(key_up4 == 1 && key4 == 0)
	{
		systick_delay_ms(10);
		key_up4 = 0;
		if(key4 == 0) 
            return 1;
	}
    
	else if(key4 == 1 && key_up4 == 0)
		key_up4 = 1;
    
	return 0;
}

uint8 key_scan_key5(uint8 mode){
    
	static uint8 key_up5 = 1;
    
	if(mode == 1)
		key_up5 = 1;
    
	if(key_up5 == 1 && key5 == 0)
	{
		systick_delay_ms(10);
		key_up5 = 0;
		if(key5 == 0) 
            return 1;
	}
    
	else if(key5 == 1 && key_up5 == 0)
		key_up5 = 1;
    
	return 0;
}

uint8 key_scan_key6(uint8 mode){
    
	static uint8 key_up6 = 1;
    
	if(mode == 1)
		key_up6 = 1;
    
	if(key_up6 == 1 && key6 == 0)
	{
		systick_delay_ms(10);
		key_up6 = 0;
		if(key6 == 0) 
            return 1;
	}
    
	else if(key6 == 1 && key_up6 == 0)
		key_up6 = 1;
    
	return 0;
}


