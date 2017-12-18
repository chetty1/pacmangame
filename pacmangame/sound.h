#ifndef SOUND_H
#define SOUND_H
#include<SFML/Audio.hpp>

class sound
{
    public:
        sound();
        void PacmanDieSound();
        void OpeningSound();
        void PacmanSound();
        void Siren();
        void RetreatGhost();
        virtual ~sound();

        sf::SoundBuffer buffer;
        sf::Sound sound_1;

        sf::SoundBuffer buffer_2;
        sf::Sound sound_2;

        sf::SoundBuffer buffer_3;
        sf::Sound sound_3;

        sf::SoundBuffer buffer_4;
        sf::Sound sound_4;

        sf::SoundBuffer buffer_5;
        sf::Sound sound_5;



    protected:
    private:
};

#endif // SOUND_H
