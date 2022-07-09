#include "Speaker.h"
#include "I2SOutput.h"
#include "WAVFileReader.h"

Speaker::Speaker(I2SOutput *i2s_output)
{
    m_i2s_output = i2s_output;
    m_ok = new WAVFileReader("/ok.wav");
    m_ready_ping = new WAVFileReader("/ready_ping.wav");
    m_cantdo = new WAVFileReader("/cantdo.wav");

    // Animal Sounds
    m_animal_duck = new WAVFileReader("/duck.wav");
    m_animal_cow = new WAVFileReader("/cow.wav");
    m_animal_cat = new WAVFileReader("/cat.wav");
    m_animal_dog = new WAVFileReader("/dog.wav");
    m_animal_pig = new WAVFileReader("/pig.wav");
    m_animal_dolphin = new WAVFileReader("/dolphin.wav");
    m_animal_lion = new WAVFileReader("/lion.wav");
    m_animal_chicken = new WAVFileReader("/chicken.wav");
    m_animal_sheep = new WAVFileReader("/sheep.wav");
    m_animal_crow = new WAVFileReader("/crow.wav");
}

Speaker::~Speaker()
{
    delete m_ok;
    delete m_ready_ping;
    delete m_cantdo;
    delete m_animal_duck;
    delete m_animal_cow;
    delete m_animal_cat;
    delete m_animal_dog;
    delete m_animal_pig;
    delete m_animal_dolphin;
    delete m_animal_lion;
    delete m_animal_chicken;
    delete m_animal_sheep;
    delete m_animal_crow;
}

void Speaker::playOK()
{
    m_ok->reset();
    m_i2s_output->setSampleGenerator(m_ok);
}

void Speaker::playReady()
{
    m_ready_ping->reset();
    m_i2s_output->setSampleGenerator(m_ready_ping);
}

void Speaker::playCantDo()
{
    m_cantdo->reset();
    m_i2s_output->setSampleGenerator(m_cantdo);
}

/**
 * @brief Plays a duck sound from the speaker.
 */
void Speaker::playDuck()
{
    m_animal_duck->reset();
    m_i2s_output->setSampleGenerator(m_animal_duck);
    Serial.printf("----------- Marvin said quack! ----------");
}

/**
 * @brief Plays a cow sound from the speaker.
 */
void Speaker::playCow()
{
    m_animal_cow->reset();
    m_i2s_output->setSampleGenerator(m_animal_cow);
    Serial.printf("----------- Marvin said moo! ----------");
}

/**
 * @brief Plays a cat sound from the speaker.
 */
void Speaker::playCat()
{
    m_animal_cat->reset();
    m_i2s_output->setSampleGenerator(m_animal_cat);
    Serial.printf("----------- Marvin said meow! ----------");
}

/**
 * @brief Plays a dog sound from the speaker.
 */
void Speaker::playDog()
{
    m_animal_dog->reset();
    m_i2s_output->setSampleGenerator(m_animal_dog);
    Serial.printf("----------- Marvin said bark! ----------");
}

/**
 * @brief Plays a pig sound from the speaker.
 */
void Speaker::playPig()
{
    m_animal_pig->reset();
    m_i2s_output->setSampleGenerator(m_animal_pig);
    Serial.printf("----------- Marvin said oink! ----------");
}


/**
 * @brief Plays a dolphin sound from the speaker.
 */
void Speaker::playDolphin()
{
    m_animal_dolphin->reset();
    m_i2s_output->setSampleGenerator(m_animal_dolphin);
    Serial.printf("----------- Marvin imitated dolphin! ----------");
}

/**
 * @brief Plays a lion sound from the speaker.
 */
void Speaker::playLion()
{
    m_animal_lion->reset();
    m_i2s_output->setSampleGenerator(m_animal_lion);
    Serial.printf("----------- Marvin said roar! ----------");
}

/**
 * @brief Plays a chicken sound from the speaker.
 */
void Speaker::playChicken()
{
    m_animal_chicken->reset();
    m_i2s_output->setSampleGenerator(m_animal_chicken);
    Serial.printf("----------- Marvin said cluck! ----------");
}

/**
 * @brief Plays a sheep sound from the speaker.
 */
void Speaker::playSheep()
{
    m_animal_sheep->reset();
    m_i2s_output->setSampleGenerator(m_animal_sheep);
    Serial.printf("----------- Marvin said baa! ----------");
}

/**
 * @brief Plays a crow sound from the speaker.
 */
void Speaker::playCrow()
{
    m_animal_crow->reset();
    m_i2s_output->setSampleGenerator(m_animal_crow);
    Serial.printf("----------- Marvin said kraa! ----------");
}