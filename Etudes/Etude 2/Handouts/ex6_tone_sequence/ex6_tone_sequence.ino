/* From Spark Fun Inventor's Kit */

#define BUZZER_PIN 9
#define SONG_LENGTH 18

// lets make an array of chars: the notes in our song - a space == delay
char notes[SONG_LENGTH] = {'c', 'e', 'e', 'a', 'C', 'a', 'g', ' ', 'a', 'a', 'f', 'f', 'g' ,' ',' ', 'g', 'f', ' '}; 


// make another array for the number of beats per note 
// 4 ==1/4 note, 2==1/2 note etc...
int beats[SONG_LENGTH] = { 1, 1, 1, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 4, 4, 2};

 int tempo = 200;  // The tempo is how fast to play the song.

void setup() {

  pinMode(BUZZER_PIN, OUTPUT);

}

void loop() {

   for (int i = 0; i < SONG_LENGTH; i++) 
   // for loop is used to index through the arrays
  {
    int duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
      delay(duration);   //delay ... 
    
    else                          // otherwise, play the note
    {
      // the pin, the frequency and the length of that note
      tone(BUZZER_PIN, findFrequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
   
    delay(tempo/10);              // brief pause between notes
  }
  

}

int findFrequency(char note)
{
 const int numNotes = 8;  // number of notes we're storing
  // need to map from one to the other
  char names[numNotes] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'    };
  
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523    };

    for(int i=0; i< numNotes; i++)
    {
      if(names[i] == note)
      {
        return frequencies[i];
      }
    }

    return(0);
}



