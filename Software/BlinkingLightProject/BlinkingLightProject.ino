// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN 2
#define PWM_LED_OUT 11
#define PWM_MAX 255

// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool button_push = false;
int previous_mode = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, FALLING);
  pinMode(PWM_LED_OUT, OUTPUT);
  
}

void loop() {

  check_for_button_press();
  set_pwn_based_on_operating_mode();
  shine_led(PWM_OUT);
  
}

void button_pushed() {
      
  unsigned long previous_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - previous_interrupt_time > 500) {
    button_push = true;
  }
  previous_interrupt_time = interrupt_time;

}

void set_pwn_based_on_operating_mode() {

  switch (operating_mode) {
    case 0:
      PWM_OUT = 0;
      break;
    case 1:
      PWM_OUT = PWM_MAX;
      break;
    case 2:
      PWM_OUT = int(PWM_MAX / 2);
      break;
    case 3:
      PWM_OUT = int(PWM_MAX / 4);
      break;
    case 4:
      flash_the_light();
      break;
  }

}

void flash_the_light() {

digitalWrite(PWM_LED_OUT, HIGH);
delay((1000 / FLASH_RATE_HZ) / 2);
digitalWrite(PWM_LED_OUT, LOW);
delay((1000 / FLASH_RATE_HZ) / 2);

}

void shine_led(int PWM_OUT) {

    analogWrite(PWM_LED_OUT, PWM_OUT);

}

void check_for_button_press() {
  
  if ((button_push) && (previous_mode != 4)) {
    operating_mode = previous_mode + 1;
    button_push = false;
  }
  else if ((button_push) && (previous_mode == 4)) {
    operating_mode = 0;
    button_push = false;
  }
  previous_mode = operating_mode;
  
}

