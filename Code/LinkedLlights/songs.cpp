#include "songs.h"
#include "pitches.h"

#include "timer.h"

Song::Song(int buzzPin, int* melody, int* tempo) : beatTimer(Timer(0)), currentNoteIndex(0) {
  this->buzzPin = buzzPin;
  this->melody = melody;
  this->tempo = tempo;
};

int* Song::getMelody() {
  return this->melody;
};

int* Song::getTempo() {
  return this->tempo;
};

void Song::play() {
  this->beatTimer.Start();
};

void Song::processSong() {
  if (this->beatTimer.Check()) {
    this->currentNoteIndex++;
    if (this->currentNoteIndex >= this->melody[0]) {
      this->currentNoteIndex = 1;
      this->beatTimer.Stop();
      return;
    }

    Serial.print("Current Index = ");
    Serial.println(this->currentNoteIndex);

    int tempo = this->tempo[this->currentNoteIndex - 1];
    if (tempo == 0) {
      tempo = 1;
    }

    int currentNote = this->melody[this->currentNoteIndex];
    int noteDuration = 1000 / tempo;

    if (noteDuration < 0) {
      noteDuration *= -1;
    }
    
    this->startBuzz(currentNote, noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    this->beatTimer.SetNextInterval(pauseBetweenNotes);
  }
};

void Song::startBuzz(int note, int duration) {
  if (duration < 0) {
    duration *= -1.5;
  }

  if (note == 0) {
    delayMicroseconds(duration);
    return;
  }

  tone(this->buzzPin, note, duration * 0.9);
}

void Song::stopBuzz(int duration) {
  digitalWrite(this->buzzPin, LOW);
  this->beatTimer.SetNextInterval(duration);
}

JingleBells::JingleBells(int buzzPin) : Song(buzzPin, new int [27] { 27,
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
    NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
    NOTE_D5, NOTE_G5
  }, new int [26] {
    4, 4, 2,
    4, 4, 2,
    4, 4, 4, 4,
    1,
    4, 4, 4, 4,
    4, 4, 4, 8, 8,
    4, 4, 4, 4,
    2, 2
  }) {
}

WeWishYouAMerryChristmas::WeWishYouAMerryChristmas(int buzzPin) : Song(buzzPin, new int [31] { 31,
    NOTE_B3,
    NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
    NOTE_D4, NOTE_D4, NOTE_D4,
    NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
    NOTE_E4, NOTE_E4, NOTE_E4,
    NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
    NOTE_D4, NOTE_G4, NOTE_E4,
    NOTE_F4
  }, new int [30] {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
}) {
}

SantaClauseIsComingToTown::SantaClauseIsComingToTown(int buzzPin) : Song(buzzPin, new int [29] { 29,
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
}, new int [28] {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
}) {
}

CanonInD::CanonInD(int buzzPin) : Song(buzzPin, new int [51] { 51,
  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_FS3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_FS3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_FS3, NOTE_E3, NOTE_FS3, NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4
}, new int [50] { 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 2, 4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2 }) {
}

SuperMarioBrothers::SuperMarioBrothers(int buzzPin) : Song(buzzPin, new int [31] { 31,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5, NOTE_G5, REST, NOTE_G4, REST, NOTE_C5, NOTE_G4, REST, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5, REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4
}, new int [30] { 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 4, -4, 8, 4, -4, 4, 4, 8, 4, -8, -8, -8, 4, 8, 8, 8, 4, 8, 8, -4 }) {
}

SilentNight::SilentNight(int buzzPin) : Song(buzzPin, new int [48] { 48,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D5, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D5, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_E5, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4, NOTE_C4
}, new int [47] { -4, 8, 4, -2, -4, 8, 4, -2, 2, 4, -2, 2, 4, -2, 2, 4, -4, 8, 4, -4, 8, 4, -2, 2, 4, -4, 8, 4, -4, 8, 4, -2, 2, 4, -4, 8, 4, -2, -2, 4, 4, 4, -4, 8, 4, -2, -1 }) {
}

GameOfThrones::GameOfThrones(int buzzPin) : Song(buzzPin, new int [35] { 35,
  NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_AS3, NOTE_DS4, NOTE_D4, NOTE_F4, NOTE_AS3, NOTE_DS4, NOTE_D4, NOTE_C4
}, new int [34] { 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, -2, -2, 8, 8, 2, 2, 8, 8, 0, -2, -2, 8, 8, 2, -2, 8, 8, 0 }) {
};

AsaBranca::AsaBranca(int buzzPin) : Song(buzzPin, new int [35] { 35,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_D5, REST, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_C5, REST, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_B4, REST, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, REST, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_D5, REST, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_C5
}, new int [34] { 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4 }) {
};

BabyElephantWalk::BabyElephantWalk(int buzzPin) : Song(buzzPin, new int [69] { 69,
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_FS4, NOTE_G4, REST, REST, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_DS4, NOTE_A4, NOTE_E4, NOTE_C4, REST, REST, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_FS4, NOTE_G4, REST, REST, REST, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_B4, NOTE_G4, REST, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_C4, NOTE_G4, NOTE_AS4, NOTE_C5, REST, REST
}, new int [68] { -7, 13, 7, 7, 7, 7, 7, 7, 7, 7, 3, 2, -7, 13, 7, 7, 7, 7, 7, 7, -2, 7, 1, 7, 7, 7, 3, 2, -7, 13, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 3, 3, 7, 7, 7, 7, 3, 3, 13, 13, 13, 13, 7, 7, 3, 3, 13, 13, 13, 13, 7, 7, 7, 7, 3, 2 }) {
};

BrahmsLullaby::BrahmsLullaby(int buzzPin) : Song(buzzPin, new int [55] { 55,
  NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_G4, NOTE_AS4, REST, NOTE_G4, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_GS4, REST, NOTE_F4, NOTE_GS4, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_D5, NOTE_DS5, REST, NOTE_DS4, NOTE_DS4, NOTE_DS5, NOTE_C5, NOTE_GS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_DS4, NOTE_DS4, NOTE_DS5, NOTE_C5, NOTE_GS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_DS4
}, new int [54] { 2, 2, -2, 4, 2, 2, 2, 4, 4, 2, -2, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 1, 4, 4, 1, 4, 4, 2, 2, 2, 1, 4, 4, 1, 4, 4, 1, 4, 4, 2, 2, 2, 1 }) {
};

StarWarsCantina::StarWarsCantina(int buzzPin) : Song(buzzPin, new int [66] { 66,
  NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, REST, NOTE_AS4, NOTE_B4, NOTE_B4, NOTE_AS4, NOTE_B4, NOTE_A4, REST, NOTE_GS4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, REST, NOTE_AS4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_E5, NOTE_B4, REST, NOTE_AS4, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_AS4, NOTE_AS4, NOTE_B4, NOTE_G4,
}, new int [65] { -4, -4, -4, -4, 8, -4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, -2, -4, -4, -4, -4, 8, -4, 8, 8, 8, 8, -4, -4, 8, -4, 8, -4, -4, -4, -4, -4, -4, -4, 8, -4, 8, 8, 8, 8, 4, -4, 8, -4, -4, -2, 2, 2, 2, 2, -4, -4, 8, 8, 4, 4 }) {
};

FurElise::FurElise(int buzzPin) : Song(buzzPin, new int [37] { 37,
  NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4, NOTE_C5, REST, NOTE_E4, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_C5, NOTE_B4, NOTE_A4
}, new int [36] { 8, 8, 8, 8, 8, 8, 8, 8, -4, 8, 8, 8, -4, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, -4, 8, 8, 8, -4, 8, 8, 8, 2 }) {
};
