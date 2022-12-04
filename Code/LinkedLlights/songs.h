#ifndef Songs_h
#define Songs_h

#include <Arduino.h>
#include "pitches.h"
#include "Timer.h"

class Song {
  public:
    Song(int buzzPin, int* melody, int* tempo);
    int* getMelody();
    int* getTempo();
    void play();
    void processSong();
    
  private:
    int* melody;
    int* tempo;
    int currentNoteIndex;
    int buzzPin;
    Timer beatTimer;

    void startBuzz(int note, int duration);
    void stopBuzz(int duration);
};

class JingleBells : public Song {
  public:
    JingleBells(int buzzPin);
};

class WeWishYouAMerryChristmas : public Song {
  public:
    WeWishYouAMerryChristmas(int buzzPin);
};

class SantaClauseIsComingToTown : public Song {
  public:
    SantaClauseIsComingToTown(int buzzPin);
};

class CanonInD : public Song {
  public:
    CanonInD(int buzzPin);
};

class SuperMarioBrothers : public Song {
  public:
    SuperMarioBrothers(int buzzPin);
};

class SilentNight : public Song {
  public:
    SilentNight(int buzzPin);
};

class GameOfThrones : public Song {
  public:
    GameOfThrones(int buzzPin);
};

class AsaBranca : public Song {
  public:
    AsaBranca(int buzzPin);
};

class BabyElephantWalk : public Song {
  public:
    BabyElephantWalk(int buzzPin);
};

class BrahmsLullaby : public Song {
  public:
    BrahmsLullaby(int buzzPin);
};

class StarWarsCantina : public Song {
  public:
    StarWarsCantina(int buzzPin);
};

class FurElise : public Song {
  public:
    FurElise(int buzzPin);
};
#endif
