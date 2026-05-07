#include "Character.h"

// ================= Fighter =================

Character createBladeCombatant() {
    Character c;

    c.name = "Combatente - Laminas";
    c.role = "Combatente";
    c.specialization = "Guerreiro";

    c.attributes = { 3, 2, 1, 3, 1 };

    c.maxHealth = 65;
    c.health = c.maxHealth;
    c.defense = 22;

    c.skills.push_back({ "Fisico", "FOR", 5 });
    c.skills.push_back({ "melee", "FOR", 5 });

    c.weapons.push_back({ "Katana", "2d10", 17, 2, "melee" });
    c.weapons.push_back({ "Chainsaw", "4d6", 18, 2, "melee" });
    c.weapons.push_back({ "Scythe", "3d4", 18, 4, "melee" });
    c.weapons.push_back({ "Revolver", "2d6", 19, 3, "short" });

    c.inventory.push_back({
        "Mud Bottle",
        "healing",
        "2d6",
        2
        });

    return c;
}

Character createRangedCombatant() {
    Character c;

    c.name = "Combatente - Armas";
    c.role = "Combatente";
    c.specialization = "Operacoes Especiais";

    c.attributes = { 2, 3, 1, 2, 2 };

    c.maxHealth = 58;
    c.health = c.maxHealth;
    c.defense = 18;

    c.skills.push_back({ "Iniciativa", "AGI", 10 });
    c.skills.push_back({ "Pontaria", "AGI", 5 });

    c.weapons.push_back({ "Assault Rifle", "2d10", 19, 3, "medium" });
    c.weapons.push_back({ "Shotgun", "4d6", 20, 3, "short" });
    c.weapons.push_back({ "Sniper Rifle", "2d8", 17, 3, "long" });
    c.weapons.push_back({ "Sword", "1d10", 18, 2, "melee" });

    c.inventory.push_back({
        "Mud Bottle",
        "healing",
        "2d6",
        2
        });

    return c;
}

// ================= Occultist =================

Character createConduitOccultist() {
    Character c;

    c.name = "Ocultista - Conduite";
    c.role = "Ocultista";
    c.specialization = "Conduite";

    c.attributes = { 1, 2, 3, 1, 3 };

    c.maxHealth = 28;
    c.health = c.maxHealth;
    c.defense = 12;

    c.skills.push_back({ "Ocultismo", "INT", 5 });
    c.skills.push_back({ "Vontade", "PRE", 5 });

    c.inventory.push_back({
        "Mud Bottle",
        "healing",
        "2d6",
        2
        });

    c.rituals.push_back({
        "Eletrocussao",
        "attack",
        "A paranormal lightning strike that damages the target.",
        "short",
        "3d6",
        0
        });

    c.rituals.push_back({
        "Armadura de Sangue",
        "defense",
        "Your blood crystallizes around your body, creating armor.",
        "self",
        "",
        5
        });

    return c;
}

Character createFlagellatorOccultist() {
    Character c;

    c.name = "Ocultista - Flagelador";
    c.role = "Ocultista";
    c.specialization = "Flagelador";

    c.attributes = { 1, 1, 3, 2, 3 };

    c.maxHealth = 34;
    c.health = c.maxHealth;
    c.defense = 11;

    c.skills.push_back({ "Ocultismo", "INT", 5 });
    c.skills.push_back({ "Vontade", "PRE", 5 });

    c.inventory.push_back({
        "Mud Bottle",
        "healing",
        "2d6",
        2
        });

    c.rituals.push_back({
        "Sangue Profano",
        "attack",
        "Deals paranormal damage using the user's own life.",
        "short",
        "2d6",
        0
        });

    c.rituals.push_back({
        "Carne Resistente",
        "defense",
        "Temporarily increases defense.",
        "self",
        "",
        4
        });

    c.rituals.push_back({
        "Dor Compartilhada",
        "attack",
        "Deals paranormal damage to a nearby target.",
        "short",
        "1d12",
        0
        });

    return c;
}