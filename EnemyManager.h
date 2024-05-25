#pragma once

class EnemyManager
{
private:
    class Slime* slime;
    class Bird* bird;
    class Flower* flower;
    class Fairy* fairy;

public:

    EnemyManager(class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager);
    ~EnemyManager();

    void Update(float delta_time);
    void Draw() const;
};