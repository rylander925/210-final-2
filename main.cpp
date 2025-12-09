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

/*
Milestone 1: Coffee booth queue struct
    * Use linked list as core data structure
    * Struct contains name & drink order
    * Use LLM to create arrays of names/drinks
*/
struct CoffeeBooth {
    public:
        //initialize w/ no nodes
        CoffeeBooth() {
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
        void Push(bool showFlags = true) {
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
        void Pop(bool showFlags = true) {
            //check for empty queue
            if (!head) {
                if (showFlags) cout << "Coffee queue is empty" << endl;
                return;
            }

            //if customer exists, serve & remove from list
            CoffeeNode* deleteNode = head;
            if (showFlags) cout << "Coffee booth served " << deleteNode->name << " a " << deleteNode->flavor << endl;
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
Milestone 2: Run sim for 10 rounds
    * Init queue w/ 3 customers
    * Possibilities:
    *   0.5 join queue
    *   1.0 serve head (if not empty)
*/

/*
Milestone 3: Repeat 1 & 2 with a muffin booth
    * Use a deque as core data structure
    * run 10 round sim
        * same possibilities
    * (Can reuse names, make new muffin flavor array)
*/

/*
Milestone 4: Repeat 1 & 2 w/ friendship bracelets
    * Use vector
*/

/*
Milestone 5: Repeat 1 & 2 w/ struct of your choice
    * use queue
*/