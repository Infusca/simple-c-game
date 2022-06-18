#include "enemy.h"
#include <iostream>

Enemy::Enemy(int e) { // constructor
    energy = e;
}

bool Enemy::performSetup() {
    if (!enemyTexture.loadFromFile("assets/enemy.png")) {
        std::cout << "Could not load enemy image" << std::endl;
        return false;
    }
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(sf::Vector2f(225,250));
    enemySprite.scale(sf::Vector2f(2,2));

    if (!attackSoundBuffer.loadFromFile("assets/damage.ogg")) {
        std::cout << "Could not load audio" << std::endl;
        return false;
    }

    attackSound.setBuffer(attackSoundBuffer);

    return true;
}

void Enemy::draw(sf::RenderWindow * window) { // pass as point because need strong reference to it
    window->draw(enemySprite); // use arrow when accessing pointer
}
// when accessing sprites, windows, sounds from other classes, need to pass in as pointers:
// need strong references, not pass in copied values

bool Enemy::checkIfHit(sf::Vector2i mousePos) {
    float enemyMinX = enemySprite.getGlobalBounds().left;
    float enemyMaxX = enemySprite.getGlobalBounds().width + enemyMinX;
    float enemyMinY = enemySprite.getGlobalBounds().top;
    float enemyMaxY = enemySprite.getGlobalBounds().height + enemyMinY;

    float mouseX = mousePos.x;
    float mouseY = mousePos.y;

    return mouseX >= enemyMinX && mouseX  <= enemyMaxX && mouseY >= enemyMinY && mouseY <= enemyMaxY;    
}

bool Enemy::takeDamage(int damage){
    energy -= damage;
    attackSound.play();
    return energy <=0;
}