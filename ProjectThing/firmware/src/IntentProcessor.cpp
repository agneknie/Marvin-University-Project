#include <Arduino.h>
#include "IntentProcessor.h"
#include "Speaker.h"
#include <dotstar_wing.h>

IntentProcessor::IntentProcessor(Speaker *speaker)
{
    m_speaker = speaker;
}

/**
 * @brief Plays an animal sounds, based on the received intent.
 * 
 * @param intent receveid intent.
 * @return IntentResult result of intent processing.
 */
IntentResult IntentProcessor::animalSound(const Intent &intent)
{
    // Prints the intent information message
    Serial.printf(
      "animalSound: confidence=%.f%%; device_name=%s; trait_value=%s; trait_confidence=%.f%%\n",
       100 * intent.intent_confidence, intent.device_name.c_str(),
       intent.trait_value.c_str(), 100 * intent.trait_confidence
    );

    // Checks intent confidence is high enough
    if (intent.intent_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on intent\n", 100 * intent.intent_confidence);
        return FAILED;
    }
    // Checks intent has a sound name associated
    if (intent.device_name.empty())
    {
        Serial.println("No sound found");
        return FAILED;
    }
    // Checks intent sound name confidence is high enough
    if (intent.device_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on sound\n", 100 * intent.device_confidence);
        return FAILED;
    }

    // If all checks passed, plays the relevant sound
    // Duck sound
    if(intent.device_name == "duck")
    {
        m_speaker->playDuck();
        return SILENT_SUCCESS;
    }
    // Cow sound
    if(intent.device_name == "cow")
    {
        m_speaker->playCow();
        return SILENT_SUCCESS;
    }
    // Cat sound
    if(intent.device_name == "cat")
    {
        m_speaker->playCat();
        return SILENT_SUCCESS;
    }
    // Dog sound
    if(intent.device_name == "dog")
    {
        m_speaker->playDog();
        return SILENT_SUCCESS;
    }
    // Pig sound
    if(intent.device_name == "pig")
    {
        m_speaker->playPig();
        return SILENT_SUCCESS;
    }
    // Dolphin sound
    if(intent.device_name == "dolphin")
    {
        m_speaker->playDolphin();
        return SILENT_SUCCESS;
    }
    // Lion sound
    if(intent.device_name == "lion")
    {
        m_speaker->playLion();
        return SILENT_SUCCESS;
    }
    // Chicken sound
    if(intent.device_name == "chicken")
    {
        m_speaker->playChicken();
        return SILENT_SUCCESS;
    }
    // Sheep sound
    if(intent.device_name == "sheep")
    {
        m_speaker->playSheep();
        return SILENT_SUCCESS;
    }
    // Crow sound
    if(intent.device_name == "crow")
    {
        m_speaker->playCrow();
        return SILENT_SUCCESS;
    }
    // If no matching animal was found, informs that Marvin can't imitate this animal
    else
    {
        return FAILED;
    }
}

IntentResult IntentProcessor::turnOnDevice(const Intent &intent)
{
    Serial.printf(
      "turnOnDevice: confidence=%.f%%; device_name=%s; trait_value=%s; trait_confidence=%.f%%\n",
      100 * intent.intent_confidence, intent.device_name.c_str(),
      intent.trait_value.c_str(), 100 * intent.trait_confidence
    );

    if (intent.intent_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on intent\n", 100 * intent.intent_confidence);
        return FAILED;
    }
    if (intent.device_name.empty())
    {
        Serial.println("No device found");
        return FAILED;
    }
    if (intent.device_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on device\n", 100 * intent.device_confidence);
        return FAILED;
    }
    if (intent.trait_value.empty())
    {
        Serial.println("Can't work out the intent action");
        return FAILED;
    }
    if (intent.trait_confidence < 0.4)
    {
        Serial.printf("Only %.f%% certain on trait\n", 100 * intent.trait_confidence);
        return FAILED;
    }
    bool is_turn_on = intent.trait_value == "on";

    // global device name "lights"
    if (intent.device_name == "lights")
    {
        for (const auto &dev_pin : m_device_to_pin)
        {
            digitalWrite(dev_pin.second, is_turn_on);
        }
    }
    else if (intent.device_name == "matrix") {
      if (is_turn_on)
        dotstar_wing_on();
      else
        dotstar_wing_off();
    }
    else
    {
        // see if the device name is something we know about
        if (m_device_to_pin.find(intent.device_name) == m_device_to_pin.end())
        {
            Serial.printf("Don't recognise the device '%s'\n", intent.device_name.c_str());
            return FAILED;
        }
        digitalWrite(m_device_to_pin[intent.device_name], is_turn_on);
    }
    // success!
    return SUCCESS;
}

IntentResult IntentProcessor::processIntent(const Intent &intent)
{
    Serial.printf(
      "processIntent: name=%s; confidence=%.f%%; trait_value=%s; trait_confidence=%.f%%\n",
      intent.intent_name.c_str(), 100 * intent.intent_confidence,
      intent.trait_value.c_str(), 100 * intent.trait_confidence
    );

    if (intent.text.empty())
    {
        Serial.println("No text recognised");
        return FAILED;
    }
    Serial.printf("I heard \"%s\"\n", intent.text.c_str());
    if (intent.intent_name.empty())
    {
        Serial.println("Can't work out what you want to do with the device...");
        return FAILED;
    }
    Serial.printf("Intent is %s\n", intent.intent_name.c_str());
    if (intent.intent_name == "Turn_on_device")
    {
        return turnOnDevice(intent);
    }
    if (intent.intent_name == "Animal_sound")
    {
        return animalSound(intent);
    }

    return FAILED;
}

void IntentProcessor::addDevice(const std::string &name, int gpio_pin)
{
    m_device_to_pin.insert(std::make_pair(name, gpio_pin));
    pinMode(gpio_pin, OUTPUT);
}
