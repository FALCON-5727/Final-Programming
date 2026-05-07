#pragma once
#include <string>
#include "Character.h"

using namespace std;

// Stores the result of a skill check
struct TestResult {
    int highestRoll;
    int skillBonus;
    int total;
    bool natural20;
    bool success;
};

// Stores the current combat distance
enum CombatDistance {
    MELEE,
    SHORT,
    MEDIUM,
    LONG,
    EXTREME
};

// Stores the player's defensive reaction
enum DefenseReaction {
    NO_REACTION,
    DODGE,
    BLOCK
};

// Dice system
int rollDie(int sides);
int rollDamage(string diceExpression);
TestResult rollSkillTest(int attributeValue, int skillBonus, int difficulty);

// Menu
void clearScreen();
void pauseScreen();
void mainMenu();
Character chooseCharacter();

// Utility functions
int getAttributeValue(const Character& character, string attributeName);
int getSkillBonus(const Character& character, string skillName);
string distanceToString(CombatDistance distance);
int getRangeValue(string range);
bool isInRange(string attackRange, CombatDistance currentDistance);

// Display functions
void showCharacterStatus(const Character& character);
void showWeapons(const Character& character);
void showRituals(const Character& character);
void showInventory(const Character& character);

// Player systems
bool playerAttack(Character& player, Character& enemy, CombatDistance currentDistance);
bool playerUseRitual(Character& player, Character& enemy, CombatDistance currentDistance);
bool playerUseItem(Character& player);
CombatDistance moveCharacter(CombatDistance currentDistance);

// Enemy systems
void enemyAttack(Character& enemy, Character& player, DefenseReaction reaction);
Weapon chooseRandomEnemyWeapon(const Character& enemy);

// Combat system
DefenseReaction chooseDefenseReaction(const Character& player);
void combat(Character& player, Character& enemy);
void runCombatGauntlet(Character& player);