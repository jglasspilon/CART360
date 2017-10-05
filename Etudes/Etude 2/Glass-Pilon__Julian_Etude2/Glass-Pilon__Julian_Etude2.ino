/**********************ETUDE 2 CART 360 2017*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK. 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 5 // R PIN
#define LED_PIN_G 9 // G PIN
#define LED_PIN_B 6 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration =200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes =0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 
int mode =0; // start at off

//needed to add this boolean to keep track of whether we can record or not. Simply to prevent recording
//the same note multiple times with one button press
boolean canRecord = true;

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{ 
  pinMode(BUTTON_MODE_PIN, INPUT);

  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);

  Serial.begin(9600);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){

  //boolean to check if the button is being pressed
  bool buttonState = false;

  //boolean to check if the button has been released
  bool previousState = true;

  //output value form the mode button
  int buttonVal = digitalRead(BUTTON_MODE_PIN);

  //if the button is pressed
  if(buttonVal == HIGH){

    //check to see if we have already done something
    if(buttonState != previousState){

      //wait for input to be read
      delay(500);
      
      //cycle through the mode
      if(mode < 4){
        mode++;
      }

      else{
        mode = 0;
      }

      //alter the button state
      buttonState = !buttonState;
      previousState = buttonState;
    }
  }

  else{
    previousState != buttonState;
  }
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  //turn on the LED based on the current mode
  switch(mode){

    //OFF
    case 0:
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break;

    //BLUE
    case 1: 
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, HIGH);
      break;

    //RED
    case 2:
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break;

    //GREEN
    case 3:
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
      break;

    //PURPLE... the purple from the LED seems to be much more red than purple
    case 4:
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, HIGH);
      break;
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode ==0) { 
    reset();
  }
  else if(mode ==1) {
    live();
  }
  else if(mode ==2) {
    record();
  }
  
  else if(mode ==3) {
    play();
  }
   
  else if(mode ==4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  //reset the number of stored notes
  countNotes = 0;

  //reset the stored notes array
  for(int i = 0; i < MAX_NOTES; i++){
    notes[i] = 0;
  }
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
  //set the buzzer to play based off of the analog input from the resistor ladder.
  //the farther the switch is down the ladder, the more resistors it needs to pass through
  //and the lower frequency sound will be emitted
  tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{ 
  //set the buzzer to play based off of the analog input from the resistor ladder.
  //the farther the switch is down the ladder, the more resistors it needs to pass through
  //and the lower frequency sound will be emitted
  tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);

  //if the note from the pin is not 0 - in other words a button is pressed
  if(analogRead(NOTE_IN_PIN) != 0){

    //if we have not reached the max notes that can be recorded and we are set to record
    if(countNotes < MAX_NOTES && canRecord){

      //record a new note and increase our count
      notes[countNotes] = analogRead(NOTE_IN_PIN);
      countNotes++;

      //set it so we cannot record the same note again until the button is released
      canRecord = false;
    }
  }

  //the button is released so we can record again
  else{
    canRecord = true;
  }
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  //cycle through the recorded notes array and play them in order
  for(int i = 0; i < countNotes; i++){
    tone(BUZZER_PIN, notes[i], duration);
    delay(duration);

    //if the user is trying to change mode, break out of the loop
    if(digitalRead(BUTTON_MODE_PIN) == HIGH){
      break;
    }
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{
  //an array for the random sequence
  int randomSequence[countNotes];

  //set the values for each entry in the random sequence to a random number between 0 and the count notes
  for(int i = 0; i < countNotes; i++){
    randomSequence[i] = random(0, countNotes);
  }

  //cycle through the notes array but in the randomsequence order
  for(int i = 0; i < countNotes; i++){
    tone(BUZZER_PIN, notes[randomSequence[i]], duration);
    delay(duration);

    //if the user is trying to change mode than break out of the loop
    if(digitalRead(BUTTON_MODE_PIN) == HIGH){
      break;
    }
  }
}

/*  *  *  *  *  *                        Keyboard Analysis                         *  *  *  *  *  *
 *  The way keyboard functions (resistor ladder) is by creating mulitple posible circuits         *
 *  in series, determined by the switches. If the first switch is pressed, the current            *
 *  will pass through that switch and through only one resistor, causing a higher frequency       *
 *  sound to play since we get a higher current. However, by pressing a switch further down the   *
 *  resistor ladder, the current must pass through more resistors, therefore losing current       *
 *  along the way, resulting in a lower frequency sound due to the lower current strength.        *
 *                                                                                                *
 *  Since these switches are coneccted in parallel, any resistor added further down the ladder    *
 *  won't affect switches closer to the start of the circuit. I wanted to test this so I set up   *
 *  each resistor at 100 ohms except for the furthest resitor, which I set to 10k ohms. This      *
 *  resulted in the first 3 switches (I only used 4 switches for the sounds) to play different    *
 *  audible sounds. However, the last switch did not produce any sound. this was because the      *
 *  current was completely reduced and the piezo buzzer didn't recieve a high enough frequency    *
 *  to be played.                                                                                 *
 */



