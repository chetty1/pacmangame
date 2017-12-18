#include "sound.h"
#include<SFML/Audio.hpp>
#include<iostream>
#include"maze.h"

 maze timer;


sound::sound()
{
    //ctor
}

void sound::OpeningSound()
{

    if(!buffer.loadFromFile("Pacman_Opening_Song.wav"))
    {

        std::cout<<"Opening sound error";

    }

    sound_1.setBuffer(buffer);
    sound_1.play();

}


void sound::PacmanSound()
{
     if(!buffer_2.loadFromFile("PacmanWakaWaka.wav"))
    {

        std::cout<<"Pacman sound error";

    }

    sound_2.setBuffer(buffer_2);
    sound_2.play();



}

void sound::PacmanDieSound()
{

  if(!buffer_3.loadFromFile("Pacman_Dies.wav"))
    {

        std::cout<<"Pacman die error";

    }

    sound_3.setBuffer(buffer_3);
    sound_2.pause();
    sound_3.play();



}

void sound::Siren()
{
    if(!buffer_4.loadFromFile("pacman_background1.wav"))
    {

        std::cout<<"Siren error";

    }

    sound_4.setBuffer(buffer_4);
    sound_4.play();
    sound_4.setLoop(true);


}


void sound :: RetreatGhost(){


if(!buffer_5.loadFromFile("pacman_alarm1.wav")){

std::cout <<"Retreat error";


}


sound_5.setBuffer(buffer_5);

if(timer.edible !=1){

sound_5.play();
sound_5.setLoop(true);

}
else{


sound_5.stop();

}


}



sound::~sound()
{
    //dtor
}
