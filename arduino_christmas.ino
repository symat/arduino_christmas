#define NOTE_G3 392
#define NOTE_A3 440
#define NOTE_B3 494
#define NOTE_C4 523
#define NOTE_D4 587
#define NOTE_E4 659
#define NOTE_F4 699
#define NOTE_G4 784
#define NOTE_A4 880

int just_started = 0;

void setup() {
  pinMode(12,OUTPUT);  // Tone
  pinMode(2,OUTPUT);   // LED 1 (with a small resistor, e.g. 220 Ohm)
  pinMode(5,OUTPUT);   // LED 2 (with a small resistor, e.g. 220 Ohm)
  pinMode(9,INPUT);    // Start/Stop button (connecting to ground, if pushed)

  digitalWrite(9, HIGH);  // enable pull-up

  just_started = 1;
}

unsigned int notes[109][2]={
  {NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_G4,1},{NOTE_C4,1},{NOTE_D4,1},{NOTE_E4,4},
  {NOTE_F4,1},{NOTE_F4,1},{NOTE_F4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_D4,1},{NOTE_D4,1},{NOTE_E4,1},{NOTE_D4,2},{NOTE_G4,2},
  {NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_G4,1},{NOTE_C4,1},{NOTE_D4,1},{NOTE_E4,4},
  {NOTE_F4,1},{NOTE_F4,1},{NOTE_F4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_G4,1},{NOTE_G4,1},{NOTE_F4,1},{NOTE_D4,1},{NOTE_C4,4},
  {NOTE_G3,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_C4,1},{NOTE_G3,2},{NOTE_G3,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_C4,1},{NOTE_A3,2},
  {NOTE_A3,1},{NOTE_F4,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_B3,2},{NOTE_G4,1},{NOTE_G4,1},{NOTE_F4,1},{NOTE_D4,1},{NOTE_E4,2},
  {NOTE_G3,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_C4,1},{NOTE_G3,2},{NOTE_G3,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_C4,1},{NOTE_A3,2},
  {NOTE_A3,1},{NOTE_F4,1},{NOTE_E4,1},{NOTE_D4,1},{NOTE_G4,1},{NOTE_G4,1},{NOTE_G4,2},{NOTE_A4,1},{NOTE_G4,1},{NOTE_F4,1},{NOTE_D4,1},{NOTE_C4,4},
  {NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_E4,1},{NOTE_G4,1},{NOTE_C4,1},{NOTE_D4,1},{NOTE_E4,4},
  {NOTE_F4,1},{NOTE_F4,1},{NOTE_F4,2},{NOTE_E4,1},{NOTE_E4,1},{NOTE_E4,2},{NOTE_G4,1},{NOTE_G4,1},{NOTE_F4,1},{NOTE_D4,1},{NOTE_C4,4},
};

int prev_read = 1;
int button_pushed() {
  int read = digitalRead(9);
  if(read != prev_read) {
    delay(50);  // to avoid bouncing
  }
  if(read == 0 && prev_read == 1) {
    prev_read = read;
    return 1;
  }
  prev_read = read;
  return 0;
}

void  loop() {
  digitalWrite(2, LOW);
  digitalWrite(5, LOW);

  if (button_pushed() || just_started) {
    just_started = 0;
    for (int i=0;i<109;i++) {
      int cycle = i % 2;
      tone(12,notes[i][0],notes[i][1]*200);
      if(button_pushed()) {
        break;
      }
      delay(notes[i][1]*200+100);
      digitalWrite(2,cycle);
      digitalWrite(5,!cycle);
      if(button_pushed()) {
        break;
      }
    }
  }
  
}
