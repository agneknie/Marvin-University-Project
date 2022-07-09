#ifndef _speaker_h_
#define _speaker_h_

class I2SOutput;
class WAVFileReader;

class Speaker
{
private:
    WAVFileReader *m_ok;
    WAVFileReader *m_cantdo;
    WAVFileReader *m_ready_ping;

    // Animal Sounds
    WAVFileReader *m_animal_duck;
    WAVFileReader *m_animal_cow;
    WAVFileReader *m_animal_cat;
    WAVFileReader *m_animal_dog;
    WAVFileReader *m_animal_pig;
    WAVFileReader *m_animal_dolphin;
    WAVFileReader *m_animal_lion;
    WAVFileReader *m_animal_chicken;
    WAVFileReader *m_animal_sheep;
    WAVFileReader *m_animal_crow;    

    I2SOutput *m_i2s_output;

public:
    Speaker(I2SOutput *i2s_output);
    ~Speaker();
    void playOK();
    void playReady();
    void playCantDo();

    // Animal Sounds
    void playDuck();
    void playCow();
    void playCat();
    void playDog();
    void playPig();
    void playDolphin();
    void playLion();
    void playChicken();
    void playSheep();
    void playCrow();
};

#endif