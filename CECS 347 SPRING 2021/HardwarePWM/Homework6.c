#include <kipr/botball.h>

int main()
{
    // up = 335;
    // horizotal = 1463;
    // arm = 0;
    // left wheel = 2;
    // right wheel = 1;
    
    enable_servos();
    
    set_servo_position(0, 1463);
    msleep(1000);
    
    set_servo_position(0, 335);
    msleep(1000);   
    
    set_servo_position(0, 1463);
    msleep(1000);   
    
    motor(2,100);  
    motor(1,100);
    msleep(500);

    motor(2,-100);  
    motor(1,-100);
    msleep(500);

    motor(2,100);   
    motor(1,-100);
    msleep(2500);

    motor(2,-100);   
    motor(1,100);
    msleep(2500);

    disable_servos();
    return 0;
}
