// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN 8
#define PWM_LED_OUT 9
#define PWM_MAX 255

// global variables representing "state" across all functions
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool button_push = true;
int previous_button_state = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {

  Serial.begin(9600);
  pinMode(BUTTON_IN, INPUT);
  pinMode(PWM_LED_OUT, OUTPUT);
  attachInterrupt(BUTTON_IN, button_pushed, FALLING);
  // define output (PWM) pin connected to LED

}




// continually-running loop
// calls functions that are named as "actions"
void loop(){

    //check_for_button_press();

    //set_pwm_based_on_operating_mode();

    //shine_led();

}

void set_pwn_based_on_operating_mode() {

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
        case 1:
            PWM_OUT = PWM_MAX;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
        case 3:
            PWM_OUT = int(PWM_MAX/4);
        case 4:
            flash_the_light();
    }

}

void button_pushed() {
    button_push = true;
}

void flash_the_light() {

}

void shine_led(int PWN_OUT) {
    //digitalOutput(magic_in_here);
}

void check_button_press() {
    // set operating_mode
    // reset previous button press state, interrupt catch, etc.
}
