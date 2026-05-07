#pragma once
#include <string>
#include <vector>

using namespace std;

struct Attributes {
    int strength;
    int agility;
    int intelligence;
    int vigor;
    int presence;
};

struct Skill {
    string name;
    string attribute;
    int bonus;
};

struct Weapon {
    string name;
    string damageDice;
    int critRange;
    int critMultiplier;
    string range; // short, medium, long, extreme, melee
};

struct Ritual {
    string name;
    string type;        // "attack", "defense", "support"
    string effect;      // simple description of what the ritual does
    string range;       // "self", "short", "medium", "long", etc.
    string damageDice;  // empty if the ritual does not deal damage
    int defenseBonus;   // 0 if it does not increase defense
};

struct Item {
    string name;
    string type;        // "healing"
    string effectDice;  // example: "2d6"
    int quantity;
};

class Character {
public:
    string name;
    string role;
    string specialization;

    Attributes attributes;

    int maxHealth;
    int health;
    int defense;

    vector<Skill> skills;
    vector<Weapon> weapons;
    vector<Ritual> rituals;
    vector<Item> inventory;
};


// ===== PLAYERS =====

// Fighter (melee)
Character createBladeCombatant();

// Fighter (ranged)
Character createRangedCombatant();

// Occultist (conduit)
Character createConduitOccultist();

// Occultist (flagellator)
Character createFlagellatorOccultist();


// ===== ENEMIES =====

Character createBloodZombie();
Character createFleshAberration();
Character createMudSkeleton();
Character createEnergyDisturbed();
Character createInvoked();