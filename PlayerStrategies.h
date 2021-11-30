#include 'Player.h'

class Player;
class PlayerStrategy {
    public:
        Player* p;
        PlayerStrategy(Player* p);
        virtual void issueOrder() = 0;
        virtual void toAttack() = 0;
        virtual void toDefend() = 0;
};

class Neutral: public PlayerStrategy {
    public:
        Neutral(Player* p);
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Cheater: public PlayerStrategy {
    public:
        Cheater(Player* p);
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Human: public PlayerStrategy {
    public:
        Human(Player* p);
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Agressive: public PlayerStrategy {
    public:
        Agressive(Player* p);
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Benevolent: public PlayerStrategy {
    public:
        Benevolent(Player* p);
        void issueOrder();
        void toAttack();
        void toDefend();
};