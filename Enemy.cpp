#include "Character.h"

// ================= BLOOD =================

Character createBloodZombie() {
    Character e;

    e.name = "Blood Zombie";
    e.role = "Enemy";
    e.specialization = "Blood";

    e.attributes = { 2, 2, 0, 2, 1 };

    e.maxHealth = 25;
    e.health = e.maxHealth;
    e.defense = 12;

    e.skills.push_back({ "Senses", "PRE", 5 });

    e.weapons.push_back({ "Claws", "2d4+2", 20, 2, "melee" });

    return e;
}

Character createFleshAberration() {
    Character e;

    e.name = "Flesh Aberration";
    e.role = "Enemy";
    e.specialization = "Blood";

    e.attributes = { 3, 1, 0, 3, 1 };

    e.maxHealth = 40;
    e.health = e.maxHealth;
    e.defense = 15;

    e.skills.push_back({ "Senses", "PRE", 5 });
    e.skills.push_back({ "Physical", "FOR", 5 });
    e.skills.push_back({ "Melee", "FOR", 5 });

    e.weapons.push_back({ "Brutal Strike", "2d6+4", 20, 2, "melee" });

    return e;
}

// ================= DEATH =================

Character createMudSkeleton() {
    Character e;

    e.name = "Mud Skeleton";
    e.role = "Enemy";
    e.specialization = "Death";

    e.attributes = { 2, 2, 0, 1, 1 };

    e.maxHealth = 30;
    e.health = e.maxHealth;
    e.defense = 13;

    e.skills.push_back({ "Initiative", "AGI", 5 });
    e.skills.push_back({ "Senses", "PRE", 5 });

    e.weapons.push_back({ "Mud Claws", "2d6+1", 20, 2, "melee" });

    return e;
}

// ================= ENERGY =================

Character createEnergyDisturbed() {
    Character e;

    e.name = "Energy Disturbed";
    e.role = "Enemy";
    e.specialization = "Energy";

    e.attributes = { 1, 4, 0, 0, 0 };

    e.maxHealth = 20;
    e.health = e.maxHealth;
    e.defense = 14;

    e.skills.push_back({ "Ranged", "AGI", 5 });
    e.skills.push_back({ "Initiative", "AGI", 5 });

    e.weapons.push_back({ "Energy Shot", "2d8", 20, 2, "short" });

    return e;
}

// ================= KNOWLEDGE =================

Character createInvoked() {
    Character e;

    e.name = "Invoked";
    e.role = "Enemy";
    e.specialization = "Knowledge";

    e.attributes = { 5, 3, 3, 2, 2 };

    e.maxHealth = 70;
    e.health = e.maxHealth;
    e.defense = 17;

    e.skills.push_back({ "Ranged", "AGI", 5 });
    e.skills.push_back({ "Melee", "FOR", 5 });
    e.skills.push_back({ "Initiative", "AGI", 5 });

    e.weapons.push_back({ "Subtle Claw", "2d8+4", 20, 2, "melee" });
    e.weapons.push_back({ "Mental Burst", "2d6+4", 20, 2, "medium" });

    return e;
}