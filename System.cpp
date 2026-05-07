#include "System.h"
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

// ================= Dice System =================

int rollDie(int sides) {
    return rand() % sides + 1;
}

int rollDamage(string diceExpression) {
    int numberOfDice = 0;
    int diceSides = 0;
    int bonus = 0;

    int dPosition = diceExpression.find('d');
    int plusPosition = diceExpression.find('+');

    numberOfDice = stoi(diceExpression.substr(0, dPosition));

    if (plusPosition != string::npos) {
        diceSides = stoi(diceExpression.substr(dPosition + 1, plusPosition - dPosition - 1));
        bonus = stoi(diceExpression.substr(plusPosition + 1));
    }
    else {
        diceSides = stoi(diceExpression.substr(dPosition + 1));
    }

    int total = 0;

    cout << "Damage roll (" << diceExpression << "): ";

    for (int i = 0; i < numberOfDice; i++) {
        int roll = rollDie(diceSides);
        total += roll;

        cout << roll;

        if (i < numberOfDice - 1) {
            cout << " + ";
        }
    }

    if (bonus > 0) {
        cout << " + " << bonus;
        total += bonus;
    }

    cout << " = " << total << endl;

    return total;
}

TestResult rollSkillTest(int attributeValue, int skillBonus, int difficulty) {
    TestResult result;

    result.highestRoll = 0;
    result.skillBonus = skillBonus;
    result.total = 0;
    result.natural20 = false;
    result.success = false;

    cout << "Rolling " << attributeValue << "d20: ";

    for (int i = 0; i < attributeValue; i++) {
        int roll = rollDie(20);

        cout << roll;

        if (i < attributeValue - 1) {
            cout << ", ";
        }

        if (roll == 20) {
            result.natural20 = true;
        }

        if (roll > result.highestRoll) {
            result.highestRoll = roll;
        }
    }

    result.total = result.highestRoll + skillBonus;

    if (result.natural20 || result.total >= difficulty) {
        result.success = true;
    }

    cout << endl;
    cout << "Highest roll: " << result.highestRoll << endl;
    cout << "Skill bonus: +" << result.skillBonus << endl;
    cout << "Total: " << result.total << endl;

    if (result.natural20) {
        cout << "Natural 20! Automatic success." << endl;
    }

    if (result.success) {
        cout << "Result: SUCCESS" << endl;
    }
    else {
        cout << "Result: FAILURE" << endl;
    }

    return result;
}

// ================= Menu / Utility =================

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int getAttributeValue(const Character& character, string attributeName) {
    if (attributeName == "FOR") return character.attributes.strength;
    if (attributeName == "AGI") return character.attributes.agility;
    if (attributeName == "INT") return character.attributes.intelligence;
    if (attributeName == "VIG") return character.attributes.vigor;
    if (attributeName == "PRE") return character.attributes.presence;

    return 1;
}

int getSkillBonus(const Character& character, string skillName) {
    for (int i = 0; i < character.skills.size(); i++) {
        if (character.skills[i].name == skillName) {
            return character.skills[i].bonus;
        }
    }

    return 0;
}

string distanceToString(CombatDistance distance) {
    if (distance == MELEE) return "melee";
    if (distance == SHORT) return "short";
    if (distance == MEDIUM) return "medium";
    if (distance == LONG) return "long";
    return "extreme";
}

int getRangeValue(string range) {
    if (range == "melee" || range == "Corpo a corpo") return 0;
    if (range == "short" || range == "Short" || range == "Curto") return 1;
    if (range == "medium" || range == "Medium" || range == "Medio") return 2;
    if (range == "long" || range == "Long" || range == "Longo") return 3;
    if (range == "extreme" || range == "Extreme" || range == "Extremo") return 4;

    return 2;
}

bool isInRange(string attackRange, CombatDistance currentDistance) {
    int attackValue = getRangeValue(attackRange);
    int distanceValue = currentDistance;

    return distanceValue <= attackValue;
}

// ================= Display =================

void showCharacterStatus(const Character& character) {
    cout << "\n===== " << character.name << " =====" << endl;
    cout << "Role: " << character.role << endl;
    cout << "Specialization: " << character.specialization << endl;
    cout << "Health: " << character.health << "/" << character.maxHealth << endl;
    cout << "Defense: " << character.defense << endl;
}

void showWeapons(const Character& character) {
    cout << "\nWeapons:" << endl;

    for (int i = 0; i < character.weapons.size(); i++) {
        cout << i + 1 << ". " << character.weapons[i].name
            << " | Damage: " << character.weapons[i].damageDice
            << " | Crit: " << character.weapons[i].critRange
            << "x" << character.weapons[i].critMultiplier
            << " | Range: " << character.weapons[i].range << endl;
    }

    cout << "0. Back" << endl;
}

void showRituals(const Character& character) {
    cout << "\nRituals:" << endl;

    if (character.rituals.size() == 0) {
        cout << "No rituals available." << endl;
        return;
    }

    for (int i = 0; i < character.rituals.size(); i++) {
        cout << i + 1 << ". " << character.rituals[i].name
            << " | Type: " << character.rituals[i].type
            << " | Range: " << character.rituals[i].range;

        if (character.rituals[i].damageDice != "") {
            cout << " | Damage: " << character.rituals[i].damageDice;
        }

        if (character.rituals[i].defenseBonus > 0) {
            cout << " | Defense Bonus: +" << character.rituals[i].defenseBonus;
        }

        cout << endl;
    }

    cout << "0. Back" << endl;
}

void showInventory(const Character& character) {
    cout << "\nInventory:" << endl;

    if (character.inventory.size() == 0) {
        cout << "Inventory is empty." << endl;
        return;
    }

    for (int i = 0; i < character.inventory.size(); i++) {
        cout << i + 1 << ". " << character.inventory[i].name
            << " | Type: " << character.inventory[i].type
            << " | Effect: " << character.inventory[i].effectDice
            << " | Quantity: " << character.inventory[i].quantity << endl;
    }

    cout << "0. Back" << endl;
}

// ================= Character Selection =================

Character chooseCharacter() {
    int choice;

    cout << "\n===== CHOOSE YOUR CHARACTER =====" << endl;
    cout << "1. Blade Combatant" << endl;
    cout << "2. Ranged Combatant" << endl;
    cout << "3. Conduit Occultist" << endl;
    cout << "4. Flagellator Occultist" << endl;

    cout << "\nChoice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        return createBladeCombatant();
    case 2:
        return createRangedCombatant();
    case 3:
        return createConduitOccultist();
    case 4:
        return createFlagellatorOccultist();
    default:
        cout << "Invalid option. Defaulting to Blade Combatant.\n";
        return createBladeCombatant();
    }
}

void mainMenu() {
    int choice;
    Character player = createBladeCombatant();
    bool characterSelected = false;

    while (true) {
        clearScreen();

        cout << "========================" << endl;
        cout << "   PARANORMAL ORDER" << endl;
        cout << "========================" << endl;

        if (characterSelected) {
            cout << "Selected character: " << player.name << endl;
        }
        else {
            cout << "Selected character: None" << endl;
        }

        cout << "\n1. Start Game" << endl;
        cout << "2. Choose Character" << endl;
        cout << "3. Exit" << endl;

        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();

            if (!characterSelected) {
                cout << "No character selected. Defaulting to Blade Combatant.\n\n";
                player = createBladeCombatant();
                characterSelected = true;
            }

            runCombatGauntlet(player);
            pauseScreen();
        }
        else if (choice == 2) {
            clearScreen();

            player = chooseCharacter();
            characterSelected = true;

            clearScreen();
            cout << "Character selected:\n";
            showCharacterStatus(player);

            pauseScreen();
        }
        else if (choice == 3) {
            clearScreen();
            cout << "Exiting game..." << endl;
            break;
        }
        else {
            cout << "\nInvalid option." << endl;
            pauseScreen();
        }
    }
}

// ================= Player Systems =================

bool playerAttack(Character& player, Character& enemy, CombatDistance currentDistance) {
    if (player.weapons.size() == 0) {
        cout << player.name << " has no weapons to attack with." << endl;
        return true;
    }

    cout << "\nChoose a weapon:" << endl;
    showWeapons(player);

    int choice;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 0) {
        return false;
    }

    if (choice < 1 || choice > player.weapons.size()) {
        cout << "Invalid choice. Action lost." << endl;
        return true;
    }

    Weapon weapon = player.weapons[choice - 1];

    if (!isInRange(weapon.range, currentDistance)) {
        cout << "Target is out of range for " << weapon.name << "." << endl;
        cout << "Current distance: " << distanceToString(currentDistance) << endl;
        return true;
    }

    string skillName = "Luta";
    string attributeName = "FOR";

    if (weapon.range == "melee" || weapon.range == "Corpo a corpo") {
        skillName = "Luta";
        attributeName = "FOR";
    }
    else {
        skillName = "Pontaria";
        attributeName = "AGI";
    }

    int attributeValue = getAttributeValue(player, attributeName);
    int skillBonus = getSkillBonus(player, skillName);

    cout << "\n" << player.name << " attacks with " << weapon.name << "!" << endl;

    TestResult attackRoll = rollSkillTest(attributeValue, skillBonus, enemy.defense);

    if (attackRoll.success) {
        int damage = rollDamage(weapon.damageDice);

        if (attackRoll.highestRoll >= weapon.critRange) {
            cout << "Critical hit!" << endl;
            damage *= weapon.critMultiplier;
        }

        enemy.health -= damage;

        if (enemy.health < 0) {
            enemy.health = 0;
        }

        cout << enemy.name << " takes " << damage << " damage." << endl;
    }
    else {
        cout << player.name << " missed the attack." << endl;
    }

    return true;
}

bool playerUseRitual(Character& player, Character& enemy, CombatDistance currentDistance) {
    if (player.rituals.size() == 0) {
        cout << player.name << " has no rituals." << endl;
        return true;
    }

    showRituals(player);

    int choice;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 0) {
        return false;
    }

    if (choice < 1 || choice > player.rituals.size()) {
        cout << "Invalid choice. Action lost." << endl;
        return true;
    }

    Ritual ritual = player.rituals[choice - 1];

    cout << "\n" << player.name << " uses " << ritual.name << "!" << endl;
    cout << ritual.effect << endl;

    if (ritual.type == "attack") {
        if (!isInRange(ritual.range, currentDistance)) {
            cout << "Target is out of range for this ritual." << endl;
            return true;
        }

        int attributeValue = getAttributeValue(player, "INT");
        int skillBonus = getSkillBonus(player, "Ocultismo");

        TestResult ritualRoll = rollSkillTest(attributeValue, skillBonus, enemy.defense);

        if (ritualRoll.success) {
            int damage = rollDamage(ritual.damageDice);
            enemy.health -= damage;

            if (enemy.health < 0) {
                enemy.health = 0;
            }

            cout << enemy.name << " takes " << damage << " ritual damage." << endl;
        }
        else {
            cout << "The ritual missed." << endl;
        }
    }
    else if (ritual.type == "defense") {
        player.defense += ritual.defenseBonus;
        cout << player.name << "'s defense increased by " << ritual.defenseBonus << "." << endl;
    }
    else {
        cout << "This ritual type is not implemented yet." << endl;
    }

    return true;
}

bool playerUseItem(Character& player) {
    if (player.inventory.size() == 0) {
        cout << "Inventory is empty." << endl;
        return true;
    }

    showInventory(player);

    int choice;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 0) {
        return false;
    }

    if (choice < 1 || choice > player.inventory.size()) {
        cout << "Invalid choice. Movement action lost." << endl;
        return true;
    }

    Item& item = player.inventory[choice - 1];

    if (item.quantity <= 0) {
        cout << "You do not have any " << item.name << " left." << endl;
        return true;
    }

    if (item.type == "healing") {
        int healing = rollDamage(item.effectDice);

        player.health += healing;

        if (player.health > player.maxHealth) {
            player.health = player.maxHealth;
        }

        item.quantity--;

        cout << player.name << " heals " << healing << " HP." << endl;
        cout << "Current HP: " << player.health << "/" << player.maxHealth << endl;
    }
    else {
        cout << "This item type is not implemented yet." << endl;
    }

    return true;
}

CombatDistance moveCharacter(CombatDistance currentDistance) {
    int choice;

    cout << "\nCurrent distance: " << distanceToString(currentDistance) << endl;
    cout << "1. Move closer" << endl;
    cout << "2. Move away" << endl;
    cout << "0. Back" << endl;

    cout << "Choice: ";
    cin >> choice;

    if (choice == 0) {
        return currentDistance;
    }

    int distanceValue = currentDistance;

    if (choice == 1) {
        distanceValue--;
    }
    else if (choice == 2) {
        distanceValue++;
    }
    else {
        cout << "Invalid movement." << endl;
        return currentDistance;
    }

    if (distanceValue < 0) {
        distanceValue = 0;
    }

    if (distanceValue > 4) {
        distanceValue = 4;
    }

    cout << "New distance: " << distanceToString((CombatDistance)distanceValue) << endl;

    return (CombatDistance)distanceValue;
}

// ================= Enemy Systems =================

Weapon chooseRandomEnemyWeapon(const Character& enemy) {
    int index = rand() % enemy.weapons.size();
    return enemy.weapons[index];
}

DefenseReaction chooseDefenseReaction(const Character& player) {
    int choice;

    cout << "\nThe enemy is about to attack." << endl;
    cout << "Choose a defensive reaction:" << endl;
    cout << "1. Dodge (+Pontaria to defense)" << endl;
    cout << "2. Block (reduce damage by Luta bonus)" << endl;
    cout << "3. Do nothing" << endl;

    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) return DODGE;
    if (choice == 2) return BLOCK;

    return NO_REACTION;
}

void enemyAttack(Character& enemy, Character& player, DefenseReaction reaction) {
    if (enemy.weapons.size() == 0) {
        cout << enemy.name << " has no weapons to attack with." << endl;
        return;
    }

    Weapon weapon = chooseRandomEnemyWeapon(enemy);

    string skillName = "Melee";
    string attributeName = "FOR";

    if (weapon.range == "melee" || weapon.range == "Corpo a corpo") {
        skillName = "Melee";
        attributeName = "FOR";
    }
    else {
        skillName = "Ranged";
        attributeName = "AGI";
    }

    int attributeValue = getAttributeValue(enemy, attributeName);
    int skillBonus = getSkillBonus(enemy, skillName);

    int targetDefense = player.defense;
    int damageReduction = 0;

    if (reaction == DODGE) {
        int dodgeBonus = getSkillBonus(player, "Pontaria");
        targetDefense += dodgeBonus;

        cout << player.name << " dodges and gains +" << dodgeBonus << " defense for this attack." << endl;
    }
    else if (reaction == BLOCK) {
        damageReduction = getSkillBonus(player, "Luta");

        cout << player.name << " blocks and will reduce incoming damage by " << damageReduction << "." << endl;
    }

    cout << "\n" << enemy.name << " attacks with " << weapon.name << "!" << endl;

    TestResult attackRoll = rollSkillTest(attributeValue, skillBonus, targetDefense);

    if (attackRoll.success) {
        int damage = rollDamage(weapon.damageDice);

        if (attackRoll.highestRoll >= weapon.critRange) {
            cout << "Critical hit!" << endl;
            damage *= weapon.critMultiplier;
        }

        damage -= damageReduction;

        if (damage < 0) {
            damage = 0;
        }

        player.health -= damage;

        if (player.health < 0) {
            player.health = 0;
        }

        cout << player.name << " takes " << damage << " damage." << endl;
    }
    else {
        cout << enemy.name << " missed the attack." << endl;
    }
}

// ================= Combat System =================

void combat(Character& player, Character& enemy) {
    CombatDistance currentDistance = MEDIUM;

    clearScreen();

    cout << "\n===============================" << endl;
    cout << "COMBAT STARTED" << endl;
    cout << player.name << " VS " << enemy.name << endl;
    cout << "Starting distance: " << distanceToString(currentDistance) << endl;
    cout << "===============================" << endl;

    pauseScreen();

    while (player.health > 0 && enemy.health > 0) {
        bool standardActionUsed = false;
        bool movementActionUsed = false;
        bool turnEnded = false;

        while (!turnEnded && player.health > 0 && enemy.health > 0) {
            clearScreen();

            showCharacterStatus(player);
            showCharacterStatus(enemy);

            cout << "\nCurrent distance: " << distanceToString(currentDistance) << endl;

            cout << "\nYour turn:" << endl;
            cout << "1. Attack";
            if (standardActionUsed) cout << " (used)";
            cout << endl;

            cout << "2. Rituals";
            if (standardActionUsed) cout << " (used)";
            cout << endl;

            cout << "3. Inventory";
            if (movementActionUsed) cout << " (used)";
            cout << endl;

            cout << "4. Status" << endl;

            cout << "5. Move";
            if (movementActionUsed) cout << " (movement used, can spend standard action)";
            cout << endl;

            cout << "6. End turn" << endl;

            int choice;
            cout << "Choice: ";
            cin >> choice;

            clearScreen();

            if (choice == 1) {
                if (standardActionUsed) {
                    cout << "You already used your standard action." << endl;
                    pauseScreen();
                    continue;
                }

                bool usedAction = playerAttack(player, enemy, currentDistance);

                if (usedAction) {
                    standardActionUsed = true;
                    pauseScreen();
                }
            }
            else if (choice == 2) {
                if (standardActionUsed) {
                    cout << "You already used your standard action." << endl;
                    pauseScreen();
                    continue;
                }

                bool usedAction = playerUseRitual(player, enemy, currentDistance);

                if (usedAction) {
                    standardActionUsed = true;
                    pauseScreen();
                }
            }
            else if (choice == 3) {
                if (movementActionUsed) {
                    cout << "You already used your movement action." << endl;
                    pauseScreen();
                    continue;
                }

                bool usedAction = playerUseItem(player);

                if (usedAction) {
                    movementActionUsed = true;
                    pauseScreen();
                }
            }
            else if (choice == 4) {
                showCharacterStatus(player);
                showCharacterStatus(enemy);
                cout << "\nCurrent distance: " << distanceToString(currentDistance) << endl;
                pauseScreen();
            }
            else if (choice == 5) {
                if (!movementActionUsed) {
                    currentDistance = moveCharacter(currentDistance);
                    movementActionUsed = true;
                    pauseScreen();
                }
                else if (!standardActionUsed) {
                    cout << "You already used your movement action." << endl;
                    cout << "You can spend your standard action to move again." << endl;
                    currentDistance = moveCharacter(currentDistance);
                    standardActionUsed = true;
                    pauseScreen();
                }
                else {
                    cout << "You cannot move anymore this turn." << endl;
                    pauseScreen();
                }
            }
            else if (choice == 6) {
                turnEnded = true;
            }
            else {
                cout << "Invalid option." << endl;
                pauseScreen();
            }

            if (enemy.health <= 0) {
                clearScreen();
                cout << "\n" << enemy.name << " was defeated!" << endl;
                pauseScreen();
                break;
            }

            if (standardActionUsed && movementActionUsed) {
                turnEnded = true;
            }
        }

        if (enemy.health <= 0) {
            break;
        }

        clearScreen();

        DefenseReaction reaction = chooseDefenseReaction(player);

        clearScreen();
        cout << "Enemy turn:" << endl;
        enemyAttack(enemy, player, reaction);
        pauseScreen();

        if (player.health <= 0) {
            clearScreen();
            cout << "\n" << player.name << " was defeated!" << endl;
            pauseScreen();
            break;
        }
    }

    clearScreen();
    cout << "\nCombat ended." << endl;
    pauseScreen();
}

void runCombatGauntlet(Character& player) {
    Character enemies[5] = {
        createBloodZombie(),
        createMudSkeleton(),
        createEnergyDisturbed(),
        createFleshAberration(),
        createInvoked()
    };

    for (int i = 0; i < 5; i++) {
        clearScreen();

        cout << "Next enemy: " << enemies[i].name << endl;
        pauseScreen();

        combat(player, enemies[i]);

        if (player.health <= 0) {
            clearScreen();
            cout << "\nYou died. Game over." << endl;
            return;
        }

        player.health = player.maxHealth;

        clearScreen();
        cout << "\nYou defeated " << enemies[i].name << "!" << endl;
        cout << "Your health has been restored for the next fight." << endl;
        cout << "Used items do not come back." << endl;
        pauseScreen();
    }

    clearScreen();
    cout << "\nYou survived all enemies. Victory!" << endl;
}