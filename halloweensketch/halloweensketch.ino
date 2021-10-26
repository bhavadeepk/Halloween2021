

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 10 // Change this to match the neopixels

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04


// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

#include "pitches.h"

int musicPin = 10;


//Halloween Theme
int melody[] = {NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_D5, NOTE_FS5,
                NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_D5, NOTE_FS5,
                NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS5, NOTE_F5,
                NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS5, NOTE_F5,
                NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5,
                NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5
               };
int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                       4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                      };


// Ways to improve this sketch - remove dependancy on delays and measure elapsed Time instead
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  noTone(musicPin);
  //Serial
}





void loop() {
  long duration, inches, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  // Modify the distance that you want to check for here, it's saying it must be greater than 0 but less than 20 inches
  if (inches < 20 && > 0 )
  {
    playTheSound();
  } else {
    delay(100);
    //start the flickr againS
    flickrEyes();
  }

}

void playTheSound() {
  noTone(musicPin);
  //Play Music
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 58; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(musicPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(musicPin);
  }
}

//https://github.com/schnoggo/jack-o-candle/blob/master/jack-o-candle.ino
void flickrEyes() {
  int r = 226, g = 121, b = 35;

  //  Purple flame:
  //  int r = 158, g = 8, b = 148;

  //  Green flame:
  //int r = 74, g = 150, b = 12;

  //  Flicker, based on our initial RGB values
  for (int i = 0; i < pixels.numPixels(); i++) {
    int flicker = random(0, 55);
    int r1 = r - flicker;
    int g1 = g - flicker;
    int b1 = b - flicker;
    if (g1 < 0) g1 = 0;
    if (r1 < 0) r1 = 0;
    if (b1 < 0) b1 = 0;
    pixels.setPixelColor(i, r1, g1, b1);
  }
  pixels.show();

  //  Adjust the delay here, if you'd like.  Right now, it randomizes the
  //  color switch delay to give a sense of realism
  delay(random(10, 113));
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
