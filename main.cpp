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
            //Gauranteed to serve a customer
            cout << "\t\t" << simulationName << ": ";
            Pop();

            //Chance customer joins queue
            if ((rand() % 100) < JOIN_PERCENT) { //0-49 satisfies condition
                cout << "\t\t" << simulationName << ": ";
                Push();
            }
            cout << endl;
        }

        /**
         * Output queue
         */
        virtual void Print() = 0;
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
            if (showFlags) cout << node->name << " joined the queue" << endl;
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
                if (showFlags) cout << "Queue is empty" << endl;
                return;
            }

            //if customer exists, serve & remove from list
            CoffeeNode* deleteNode = head;
            if (showFlags) cout << "Served " << deleteNode->name << " a coffee: " << deleteNode->flavor << endl;
            if (deleteNode->next) {
                head = deleteNode->next;
            } else {
                head = tail = nullptr;
            }

            delete deleteNode;
        }

        /**
         * Output queue contents
         */
        void Print() override {
            cout << "Coffee queue: " << endl;
            CoffeeNode* node = head;
            int num = 0;
            //traverse list and output names
            while (node) {
                cout << "\t" << ++num << ". " << node->name << "(" << node->flavor << ")" << endl;
                node = node->next;
            }
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
    //By default, initialize simulation name
    MuffinBooth() {
        simulationName = "Muffin Booth";
    }

    /**
     * Remove customer from queue
     * @param showFlags If true, output messages
     */
    void Pop(bool showFlags = true) override {
        //check if queue is empty before removing
        if (queue.empty()) {
            if (showFlags) cout << "Queue is empty" << endl;
            return;
        }

        //if not empty, remove customer from front of queue
        MuffinNode customer = queue.front();
        if (showFlags) cout << "Serving customer " << customer.name << " a muffin: " << customer.flavor << endl;
        queue.pop_front(); 
    }

    /**
     * Add customer to queue
     * @param showFlags If true, output messages
     */
    void Push(bool showFlags = true) override {
        //create a new customer and add to back of queue
        MuffinNode customer;
        if (showFlags) cout << customer.name << " joined the queue" << endl;
        queue.push_back(customer);
    }

    /**
     * Output queue
     */
    void Print() override {
        cout << "Muffin booth queue:" << endl;
        int num = 0;
        //traverse queue and output customer details
        for (MuffinNode customer : queue) {
            cout << '\t' << ++num << ". " << customer.name << " (" << customer.flavor << ")" << endl;
        }
    }

    private:
        struct MuffinNode {
            string name;
            string flavor;
            //by default, fill random name & flavor
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
    //By default, initialize simulation name
    BraceletBooth() {
        simulationName = "Friendship Bracelet Booth";
    }

    /**
     * Remove customer from queue
     * @param showFlags If true, output messages
     */
    void Pop(bool showFlags = true) override {
        //check if queue is empty
        if (queue.empty()) {
            if (showFlags) cout << "Queue is empty" << endl;
            return;
        }

        //if not, remove customer from front of vector
        BraceletNode customer = queue.front();
        if (showFlags) cout << "Taking customer " << customer.name << "'s bracelet order: " << customer.bracelet << endl;
        queue.erase(queue.begin());
    }

    /**
     * Add customer to queue
     * @param showFlags If true, output messages
     */
    void Push(bool showFlags = true) override {
        //add customer to back of vector
        BraceletNode customer;
        if (showFlags) cout << customer.name << " joined the queue" << endl;
        queue.push_back(customer);
    }

    private:
        struct BraceletNode {
            string name;
            string bracelet;

            //by default initialize w/ random name & bracelet
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
    use dynamically allocated array
*/
struct DonutBooth : public Simulation {
    //initialize array based on total possible customers joining list, + some wiggle room, will simply shift front position to remove from queue
    DonutBooth(int rounds, int initialCustomers) {
        queue = new DonutNode[rounds * 2 + initialCustomers]; //allocate memory to list 
        front = 0;
        back = 0;
        simulationName = "Donut Booth";
    }

    /**
     * Remove customer from queue
     * @param showFlags Show messages if true
     */
    void Pop(bool showFlags = true) override {
        //check for empty queue, back is one after the final person
        if ((front - back) == 0) {
            if (showFlags) cout << "Queue is empty" << endl;
            return;
        }

        //if not empty, serve customer
        DonutNode customer = queue[front];
        if (showFlags) cout << "Serving customer " << customer.name << " a donut: " << customer.flavor << endl;
        front++; //shift front of queue up one to 'remove' from queue
    }

    /**
     * Add customer to queue
     * @param showFlags Show messages if true
     */
    void Push(bool showFlags = true) override {
        DonutNode customer;
        if (showFlags) cout << customer.name << " joined the queue" << endl;
        queue[back++] = customer; //post inc to maintain back as one after final person
    } 

    //free memory from dynamically allocated array
    ~DonutBooth() {
        delete [] queue;
    }

    private:
        struct DonutNode {
            string name;
            string flavor;

            //initializer gives random name & donut flavor
            DonutNode() {
                name = NAMES[rand() % NUM_NAMES];
                flavor = DONUT_NAMES[rand() % NUM_FLAVORS];
            }
        };
        DonutNode* queue;
        int front; //stores front of queue, update as goes along
        int back; //stores index of back of queue (1 after the final person)
        static const int NUM_FLAVORS = 20;
        static const string DONUT_NAMES[NUM_FLAVORS];
};

const string DonutBooth::DONUT_NAMES[NUM_FLAVORS] = { //generated from ChatGPT
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
    DonutBooth donut(DEFAULT_ROUNDS, DEFAULT_CUSTOMERS);
    vector<Simulation*> simulations = {&coffee, &muffin, &bracelet, &donut};
    
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