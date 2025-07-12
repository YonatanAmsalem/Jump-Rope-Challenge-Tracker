#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define TILT_PIN 2
#define BUZZER_PIN 11
#define GREEN_LED_PIN 12

LiquidCrystal_I2C lcd(0x27, 16, 2);  //main lcd 
LiquidCrystal_I2C lcd2(0x20, 16, 2); //timer lcd

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- Global Variables ---
int selectedLevel = 0; 
int requiredJumps = 0;
unsigned long lastJumpTime = 0; //last time of jump
int jumpCount = 0;
bool goalReached = false;
volatile unsigned long secondsElapsed = 0; 

void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd2.init(); 
  lcd2.backlight();

  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  setupTimer1();  
  chooseLevel();
}

void loop() {
  runJumpSession(); 
}

void printOnLCD(const char* line1, const char* line2 = "") {
  lcd.clear(); lcd.setCursor(0, 0); lcd.print(line1);
  lcd.setCursor(0, 1); lcd.print(line2);
}

void updateTimeOnLCD2() {
  if (goalReached) {
    lcd2.clear();  
    return;
  }

  int minutes = secondsElapsed / 60;
  int seconds = secondsElapsed % 60;

  lcd2.setCursor(0, 0);
  lcd2.print("Time: ");
  if (minutes < 10) lcd2.print('0');
  lcd2.print(minutes);
  lcd2.print(':');
  if (seconds < 10) lcd2.print('0');
  lcd2.print(seconds);
  lcd2.print("    "); 
}

void setupTimer1() {
  cli(); 
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;  
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  TIMSK1 |= (1 << OCIE1A); 
  sei(); 
}

ISR(TIMER1_COMPA_vect) {
  secondsElapsed++;
}

void chooseLevel() {
  printOnLCD("Select level", "from 1 to 5");
  while (true) {
    char key = keypad.getKey();
    if (key != NO_KEY && isDigit(key)) {
      int level = key - '0';
      if (level >= 1 && level <= 5) {
        selectedLevel = level;
        requiredJumps = setRequiredJumpsForLevel(level);
        char line1[16], line2[16];
        sprintf(line1, "Level %d selected", level);
        sprintf(line2, "Target: %d jumps", requiredJumps);
        printOnLCD(line1, line2);
        delay(2000);
        break;
      } else {
        printOnLCD("Invalid level!", "Choose 1 to 5");
        delay(1500);
        printOnLCD("Select level", "from 1 to 5");
      }
    }
  }
}

int setRequiredJumpsForLevel(int level) {
  switch (level) {
    case 1: return 9;
    case 2: return 14;
    case 3: return 20;
    case 4: return 28;
    case 5: return 35;
    default: return 0;
  }
}

void runJumpSession() {
  jumpCount = 0;
  goalReached = false;
  lastJumpTime = 0;
  secondsElapsed = 0;

  unsigned long sessionDuration = (selectedLevel >= 4) ? 80 : 60;

  printOnLCD("Start jumping!", "Good luck :)");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jumps: 0");

  while (secondsElapsed < sessionDuration) {
    checkJump();
    updateTimeOnLCD2();  // הצגת זמן בזמן אמת
    if (goalReached) break;
  }

  if (!goalReached) {
    printOnLCD("Time's up!", "Goal not reached");
    delay(2000);
  }

  digitalWrite(GREEN_LED_PIN, LOW);
  askNextAction();
}

void checkJump() {
  if (digitalRead(TILT_PIN) == LOW) {
    unsigned long currentTime = millis();
    if (currentTime - lastJumpTime > 2000) {
      jumpCount++;
      lastJumpTime = currentTime;
      lcd.setCursor(0, 1);
      lcd.print("Jumps: ");
      lcd.print(jumpCount);
    }

    if (jumpCount >= requiredJumps && !goalReached) {
      goalReached = true;
      onJumpGoalReached();
    }
  }
}

void onJumpGoalReached() {
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  printOnLCD("Goal achieved!");
  delay(2000);
}

void askNextAction() {
  printOnLCD("Next step?", "A=Again B=Level C=Exit");
  while (true) {
    char key = keypad.getKey();
    if (key == 'A') {
      return;
    } else if (key == 'B') {
      chooseLevel();
      return;
    } else if (key == 'C') {
      printOnLCD("Goodbye!");
      while (true);
    }
  }
}
