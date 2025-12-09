/*
COMSC-210 | Final 2 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <array>

using namespace std;

const int NUM_NAMES = 100;
const int DEFAULT_ROUNDS = 10;
const int DEFAULT_CUSTOMERS = 3;

const string NAMES[100] = { //generated using ChatGPT
    "Aiden", "Bella", "Caleb", "Diana", "Ethan",
    "Fiona", "Gavin", "Hannah", "Isaac", "Jade",
    "Kai", "Luna", "Mason", "Nora", "Owen",
    "Piper", "Quinn", "Riley", "Sawyer", "Tessa",
    "Uriel", "Vera", "Wyatt", "Xavier", "Yara",
    "Zane", "Adrian", "Brielle", "Carter", "Delilah",
    "Elijah", "Freya", "Grayson", "Hazel", "Ian",
    "Jasmine", "Kendall", "Logan", "Mila", "Nolan",
    "Olive", "Peyton", "Reid", "Sienna", "Tristan",
    "Una", "Valerie", "Weston", "Ximena", "Yusuf",
    "Zara", "Ariana", "Blake", "Connor", "Daisy",
    "Emmett", "Faith", "Gianna", "Hunter", "Isla",
    "Jaxon", "Keira", "Levi", "Maya", "Noah",
    "Opal", "Paxton", "Rowan", "Stella", "Trevor",
    "Uriah", "Vivian", "Walker", "Xander", "Yvette",
    "Zeke", "Alexis", "Brooks", "Chloe", "Declan",
    "Eden", "Finn", "Gemma", "Hudson", "Ivy",
    "Jonah", "Kira", "Landon", "Morgan", "Nova",
    "Omar", "Parker", "Rhea", "Sydney", "Tanner",
    "Ulric", "Violet", "Wesley", "Xenia", "Zion"
};

//class to provide common simulation functionalities accross booths
class Simulation {
    public:
        /**
         * Adds customer to queue
         * @param showFlags True by default, shows serving messages
         */
        virtual void Push(bool showFlags = true) = 0;

        /**
         * Removes customer from front of queue
         * @param showFlags True by default, shows serving messages
         */
        virtual void Pop(bool showFlags = true) = 0;

        /**
         * Simulate a simulation round
         */
        void SimulateRound() {
            cout << "\t\t" << simulationName << ": ";
            Pop();

            if ((rand() % 100) < JOIN_PERCENT) { //0-49 satisfies condition
                cout << "\t\t" << simulationName << ": ";
                Push();
            }
            cout << endl;
        }
    protected:
        string simulationName;
    private:
        static const int JOIN_PERCENT = 50;
};

/*
Milestone 1: Coffee booth queue struct
    * Use linked list as core data structure
    * Struct contains name & drink order
    * Use LLM to create arrays of names/drinks
*/
struct CoffeeBooth : public Simulation {
    public:
        //initialize w/ no nodes
        CoffeeBooth() {
            simulationName = "Coffee Booth";
            head = nullptr;
            tail = nullptr;
        }

        ~CoffeeBooth() {
            //remove all nodes from list
            while(head) Pop(false);
        }

        /**
         * Add customer to back of the linked list
         * Output name of customer
         * @param showFlags True by default, will output name when called
         */
        void Push(bool showFlags = true) override {
            CoffeeNode* node = new CoffeeNode(); //next points to nullptr by default
            if (tail) {
                tail->next = node;
            } else {
                head = node;
            }
            if (showFlags) cout << node->name << " joined the coffee queue" << endl;
            tail = node;
        }

        /**
         * Remove customer from front of the linked list
         * Output information about customer served
         * @param showFlags True by default, will output if empty or customer if served
         */
        void Pop(bool showFlags = true) override {
            //check for empty queue
            if (!head) {
                if (showFlags) cout << "Coffee queue is empty" << endl;
                return;
            }

            //if customer exists, serve & remove from list
            CoffeeNode* deleteNode = head;
            if (showFlags) cout << "Coffee booth served " << deleteNode->name << " a coffee named: " << deleteNode->flavor << endl;
            if (deleteNode->next) {
                head = deleteNode->next;
            } else {
                head = tail = nullptr;
            }

            delete deleteNode;
        }
        
    private:
        static const int NUM_FLAVORS = 20;
        static const string COFFEE_FLAVORS[NUM_FLAVORS];

        struct CoffeeNode {
            string name;
            string flavor;
            CoffeeNode* next;

            //Initialize node w/ random name & flavor
            CoffeeNode() {
                next = nullptr;
                name = NAMES[rand() % NUM_NAMES];
                flavor = COFFEE_FLAVORS[rand() % NUM_FLAVORS];
            }
        };
        CoffeeNode* head;
        CoffeeNode* tail;
};

const string CoffeeBooth::COFFEE_FLAVORS[NUM_FLAVORS] = { //generated using ChatGPT
            "Espresso", "Americano", "Latte", "Cappuccino", "Mocha",
            "Macchiato", "Flat White", "Cortado", "Affogato", "Ristretto",
            "Doppio", "Irish Coffee", "Frappe", "Cold Brew", "Nitro Brew",
            "Turkish Coffee", "Vienna", "Red Eye", "Long Black", "Cafe Au Lait"
            };

/*
Milestone 3: Repeat 1 & 2 with a muffin booth
    * Use a deque as core data structure
    * run 10 round sim
        * same possibilities
    * (Can reuse names, make new muffin flavor array)
*/
struct MuffinBooth : public Simulation {
    MuffinBooth() {
        simulationName = "Muffin Booth";
    }

    void Pop(bool showFlags = true) override {
        if (queue.empty()) {
            if (showFlags) cout << "Queue is empty" << endl;
            return;
        }

        MuffinNode customer = queue.front();
        if (showFlags) cout << "Serving customer " << customer.name << " a muffin: " << customer.flavor << endl;
        queue.pop_front(); 
    }

    void Push(bool showFlags = true) override {
        MuffinNode customer;
        if (showFlags) cout << customer.name << " joined the queue" << endl;
        queue.push_back(customer);
    }

    private:
        struct MuffinNode {
            string name;
            string flavor;
            MuffinNode() {
                name = NAMES[rand() % NUM_NAMES];
                flavor = MUFFIN_NAMES[rand() % NUM_FLAVORS];
            }
        };
        deque<MuffinNode> queue;
        static const int NUM_FLAVORS = 20;
        static const string MUFFIN_NAMES[NUM_FLAVORS];
};

const string MuffinBooth::MUFFIN_NAMES[NUM_FLAVORS] = { //generated w/ ChatGPT
    "Blueberry",
    "Chocolate Chip",
    "Banana Nut",
    "Lemon Poppy Seed",
    "Double Chocolate",
    "Cranberry Orange",
    "Apple Cinnamon",
    "Pumpkin Spice",
    "Raspberry White Chocolate",
    "Strawberry Cheesecake",
    "Maple Walnut",
    "Peach Cobbler",
    "Blackberry Crumble",
    "Cinnamon Streusel",
    "Zucchini Nut",
    "Cherry Almond",
    "Vanilla Bean",
    "Mocha Swirl",
    "Honey Oat",
    "Coconut Cream"
};

/*
Milestone 4: Repeat 1 & 2 w/ friendship bracelets
    * Use vector
*/
struct BraceletBooth : public Simulation {
    BraceletBooth() {
        simulationName = "Friendship Bracelet Booth";
    }

    void Pop(bool showFlags = true) override {
        if (queue.empty()) {
            if (showFlags) cout << "Queue is empty" << endl;
            return;
        }

        BraceletNode customer = queue.front();
        if (showFlags) cout << "Taking customer " << customer.name << "'s bracelet order: " << customer.bracelet << endl;
        queue.erase(queue.begin());
    }

    void Push(bool showFlags = true) override {
        BraceletNode customer;
        if (showFlags) cout << customer.name << " joined the queue" << endl;
        queue.push_back(customer);
    }

    private:
        struct BraceletNode {
            string name;
            string bracelet;
            BraceletNode() {
                name = NAMES[rand() % NUM_NAMES];
                bracelet = BRACELET_NAMES[rand() % NUM_BRACELETS];
            }
        };
        vector<BraceletNode> queue;
        static const int NUM_BRACELETS = 20;
        static const string BRACELET_NAMES[NUM_BRACELETS];
};

const string BraceletBooth::BRACELET_NAMES[NUM_BRACELETS] = { //generated from ChatGPT
    "Chevron",
    "Candy Stripe",
    "Diagonal",
    "Diamond",
    "Zigzag",
    "Heart Pattern",
    "Braid",
    "Spiral",
    "Fishbone",
    "Double Chevron",
    "Arrowhead",
    "Wave Pattern",
    "Ladder",
    "Chinese Staircase",
    "V-Pattern",
    "Braided Bead",
    "Squared Knot",
    "Twisted Rope",
    "Herringbone",
    "Box Stitch"
};

/*
Milestone 5: Repeat 1 & 2 w/ struct of your choice
    * use standard array
*/
struct DonutBooth : public Simulation {
    DonutBooth(int rounds, int initialCustomers) {

    }

    private:
        struct DonutNode {
            string name;
            string flavor;
            DonutNode() {
                name = NAMES[rand() % NUM_NAMES];
                flavor = DONUT_NAMES[rand() % NUM_FLAVORS];
            }
        };
        static const int NUM_FLAVORS = 20;
        static const string DONUT_NAMES[NUM_FLAVORS];
};

const string DonutBooth::DONUT_NAMES[NUM_FLAVORS] = {
    "Glazed",
    "Chocolate Frosted",
    "Strawberry Sprinkle",
    "Boston Cream",
    "Jelly Filled",
    "Maple Bar",
    "Old Fashioned",
    "Blueberry Cake",
    "Powdered Sugar",
    "Cinnamon Twist",
    "Apple Fritter",
    "Vanilla Cream",
    "Cookies and Cream",
    "Caramel Crunch",
    "Lemon Filled",
    "Red Velvet",
    "S'mores",
    "Peanut Butter Cup",
    "Pumpkin Spice",
    "Coconut Cream"
};


/*
Milestone 2: Run sim for 10 rounds
    * Init queue w/ 3 customers
    * Possibilities:
    *   0.5 join queue
    *   1.0 serve head (if not empty)
*/
int main() {
    CoffeeBooth coffee;
    MuffinBooth muffin;
    BraceletBooth bracelet;
    vector<Simulation*> simulations = {&coffee, &muffin, &bracelet};
    
    //add default customers
    for (Simulation* sim : simulations) {
        for (int i = 0; i < DEFAULT_CUSTOMERS; i++) sim->Push(false);
    }

    //run simulation
    cout << "Running simulation: " << endl;
    for (int round = 1; round <= DEFAULT_ROUNDS; round++) {
        cout << "\tRound " << round << ":" << endl;
        for (Simulation* sim : simulations) sim->SimulateRound();
    }
}