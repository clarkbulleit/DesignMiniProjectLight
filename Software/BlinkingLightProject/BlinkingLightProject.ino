// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN 8
#define PWM_LED_OUT 9
#define PWM_MAX 255

// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool button_push = false;
int previous_mode = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {

  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, FALLING);
  pinMode(PWM_LED_OUT, OUTPUT);

}

void loop() {

  check_for_button_press();

  set_pwn_based_on_operating_mode();

  shine_led();
}

void button_pushed() {
  button_push = true;
}

void set_pwn_based_on_operating_mode() {
  switch (operating_mode) {
    case 0:
      PWM_OUT = 0;
    case 1:
      PWM_OUT = PWM_MAX;
    case 2:
      PWM_OUT = int(PWM_MAX / 2);
    case 3:
      PWM_OUT = int(PWM_MAX / 4);
    case 4:
      flash_the_light();
  }
}

void flash_the_light() {
  digitalWrite(PWM_LED_OUT, HIGH);
  delay((1000 / FLASH_RATE_HZ) / 2);
  digitalWrite(PWM_LED_OUT, LOW);
  delay((1000 / FLASH_RATE_HZ) / 2);
}

void shine_led(int PWM_OUT) {
  if (operating_mode != 4) {
    analogWrite(PWM_LED_OUT, PWM_OUT);
  }
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
}

