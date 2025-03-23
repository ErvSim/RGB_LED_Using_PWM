#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" 
#include <string.h>



int main()  //we are using GP16,17,18 for red, green and blue respectively
{
    int brightness_percentage;
    int BPConvertion;
    char color[10];

    stdio_init_all();
    gpio_set_function(16,GPIO_FUNC_PWM);
    gpio_set_function(17,GPIO_FUNC_PWM);
    gpio_set_function(18,GPIO_FUNC_PWM);
    
    uint slice_red   = pwm_gpio_to_slice_num(16);
    uint channel_red = pwm_gpio_to_channel(16);

    uint slice_green   = pwm_gpio_to_slice_num(17);
    uint channel_green = pwm_gpio_to_channel(17);

    uint slice_blue   = pwm_gpio_to_slice_num(18);
    uint channel_blue = pwm_gpio_to_channel(18);

    pwm_set_wrap(slice_red,65535);
    pwm_set_wrap(slice_green,65535);
    pwm_set_wrap(slice_blue,65535);
    pwm_set_clkdiv(slice_red,1.9f);
    pwm_set_clkdiv(slice_blue,1.9f);
    pwm_set_clkdiv(slice_green,1.9f);
    pwm_set_enabled(slice_red,true);
    pwm_set_enabled(slice_blue,true);
    pwm_set_enabled(slice_green,true);

    uint redPercentage = 0;
    uint greenPercentage = 0;
    uint bluePercentage = 0;
    sleep_ms(1000);
    do
    {  
        printf("\nPlease choose red, green, blue or exit \n");
        scanf("%s", &color);
        printf("You entered: %s\n", color);
        if(strcmp(color,"red")==0)
        {
            printf("Enter brightness %:\n");
            scanf("%d", &brightness_percentage);
            printf("You entered: %d\n", brightness_percentage);
            if(brightness_percentage < 0)
            {
                brightness_percentage = 0;
            }
            else if (brightness_percentage > 100)
            {
                brightness_percentage = 100;
            }
            redPercentage = brightness_percentage;
            BPConvertion = 65535 * (brightness_percentage/100.0f);
            pwm_set_chan_level(slice_red,channel_red,BPConvertion);

        }
        else if(strcmp(color,"green")==0)
        {
            printf("Enter brightness %:\n");
            scanf("%d", &brightness_percentage);
            printf("You entered: %d\n", brightness_percentage);
            if(brightness_percentage < 0)
            {
                brightness_percentage = 0;
            }
            else if (brightness_percentage > 100)
            {
                brightness_percentage = 100;
            }
            greenPercentage = brightness_percentage;
            BPConvertion = 65535 * (brightness_percentage/100.0f);
            pwm_set_chan_level(slice_green,channel_green,BPConvertion);

        }
        else if(strcmp(color,"blue")==0)
        {
            printf("Enter brightness %:\n");
            scanf("%d", &brightness_percentage);
            printf("You entered: %d\n", brightness_percentage);
            if(brightness_percentage < 0)
            {
                brightness_percentage = 0;
            }
            else if (brightness_percentage > 100)
            {
                brightness_percentage = 100;
            }
            bluePercentage = brightness_percentage;
            BPConvertion = 65535 * (brightness_percentage/100.0f);
            pwm_set_chan_level(slice_blue,channel_blue,BPConvertion);

        }
        else if(strcmp(color, "exit") == 0)
        {
            printf("Hope you enjoyed the show!\n");
            pwm_set_chan_level(slice_red,channel_red,0);
            pwm_set_chan_level(slice_green,channel_green,0);
            pwm_set_chan_level(slice_blue,channel_blue,0);
            redPercentage = 0;
            greenPercentage = 0;
            bluePercentage = 0;
        }
        else
        {
            printf("Invalid Answer, please try again\n");
        }

        printf("Red Color Duty Cycle: %u\n", redPercentage);
        printf("Green Color Duty Cycle: %u\n", greenPercentage);
        printf("Blue Color Duty Cycle: %u\n", bluePercentage);
    }while(!strcmp(color, "exit") == 0);
}


