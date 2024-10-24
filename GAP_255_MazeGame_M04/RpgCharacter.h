#pragma once

#include <string>
#include <iostream>

class RpgCharacter
{
private:
    std::string m_name;
    int m_hp;
    int m_attack;
    int m_accuracy;
    bool m_isDefending = false;
    bool m_powerAttackNext = false;
    bool m_isVulnerable = false;
    int m_defendTurnsLeft = 0;

public:
    // Constructor for initializing character with stats
    RpgCharacter(std::string name, int hp, int attack, int accuracy)
        : m_name(name), m_hp(hp), m_attack(attack), m_accuracy(accuracy) {}

    // Get fighter's name
    std::string GetName() const { return m_name; }


    //print fighters stats
    void PrintStats() const
    {
        std::cout << m_name << std::endl;
        std::cout << "Hp       :" << m_hp << std::endl;
        std::cout << "Attack   :" << m_attack << std::endl;
        std::cout << "Accuracy :" << m_accuracy << std::endl;
        std::cout << std::endl;
    }

    // Print character status
    void PrintStatus() const {
        std::cout << m_name << " has " << m_hp << " HP remaining." << std::endl;
    }

    void TakeDamage(int damage) {
        m_hp -= damage;
        if (m_hp < 0) m_hp = 0;
        PrintStatus();
    }

    bool IsAlive() const { return m_hp > 0; }

    bool IsDead() const { return m_hp <= 0; }

    void Attack(RpgCharacter& target) {
        if (m_defendTurnsLeft > 0) {
            m_defendTurnsLeft--;
        }
        else {
            m_isDefending = false;
        }


        // reduce accuracy if defending
        int actualAccuracy = m_isDefending ? m_accuracy / 2 : m_accuracy;

        // adding vulnerable because of power attack
        if (target.m_isVulnerable == true)
        {
            actualAccuracy += 10;
        }
        m_isVulnerable = false;

        // power attack
        if (m_powerAttackNext) {
            std::cout << m_name << " is performing a power attack!\n";
            actualAccuracy += 20;
            m_powerAttackNext = false;
            m_isVulnerable = true;
        }


        int random = rand() % 100;
        if (random < actualAccuracy) {
            std::cout << m_name << " hits " << target.GetName() << " for " << m_attack << " damage.\n";
            target.TakeDamage(m_attack);
        }
        else {
            std::cout << m_name << " misses!\n";
        }
    }

    void Defend() {
        std::cout << m_name << " is defending!\n";
        m_isDefending = true;
        m_defendTurnsLeft = 1;
        m_powerAttackNext = true;
    }
};