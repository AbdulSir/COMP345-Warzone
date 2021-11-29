#include 'Player.h'

class Player;
class PlayerStrategy {
    public:
        Player* p;
        virtual void issueOrder() = 0;
        virtual void toAttack() = 0;
        virtual void toDefend() = 0;
};

class Neutral: public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Cheater: public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Human: public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Agressive: public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class Benevolent: public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};