#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>

using namespace std;

// Custom comparison for priority queue of next meals
auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {return a.second < b.second;};

struct Ingredient {
    string name;
    int priority = -1;
};

struct MealPriority {
    string name;
    int priority = -1;
    bool operator<(const MealPriority& other) const {
        return priority >= other.priority; // use the default maxHeap as a minHeap
    }
};

Ingredient* generateIngredientList(string* ingredientNames, int* priorities, int numIngredients) {
    Ingredient* ingredients = new Ingredient[numIngredients];
    for (int i = 0; i < numIngredients; i++) {
        ingredients[i].name = ingredientNames[i];
        ingredients[i].priority = priorities[i];
    }
    return ingredients;
}

class Meal {
    private:
        
    public:
        string name;
        int numIngredients;
        Ingredient* ingredients;

        Meal(string name, int numIngredients, Ingredient* inputIngredients) {
            this->name = name;
            this->numIngredients = numIngredients;
            this->ingredients = inputIngredients;
        }

        int searchIngredient(string IngredientName) {
            for (int i = 0; i < numIngredients; i++) {
                if (ingredients[i].name == IngredientName) {
                    return i;
                }
            }
            return -1;
        }

        void updatePriority(string ingredientName, int priority) {
            int index = searchIngredient(ingredientName);
            if (index == -1) {
                return;
            } else {
                ingredients[index].priority = priority;
            }
        }

        void prioritize(string ingredientName) {
            int index = searchIngredient(ingredientName);
            if (index == -1) {
                return;
            } else {
                ingredients[index].priority--;
            }
        }

        int getIngredientPriority(string ingredientName) {
            int index = searchIngredient(ingredientName);
            if (index != -1) {
                return ingredients[index].priority;
            }
            return -1;
        }

        int getTotalPriority() {
            int total = 0;
            for (int i = 0; i < numIngredients; i++) {
                total += ingredients[i].priority;
            }
            return total;
        }

        int numberCommonIngredients(Meal* other) {
            int commonIngredients = 0;
            for (int i = 0; i < numIngredients; i++) {
                for (int j = 0; j < other->numIngredients; j++) {
                    if (ingredients[i].name == other->ingredients[j].name) {
                        commonIngredients++;
                        break;
                    }
                }
            }
            return commonIngredients;
        }

        vector<string> getCommonIngredients(Meal* other) {
            vector<string> commonIngredients;
            for (int i = 0; i < numIngredients; i++) {
                for (int j = 0; j < other->numIngredients; j++) {
                    if (ingredients[i].name == other->ingredients[j].name) {
                        commonIngredients.push_back(ingredients[i].name);
                        break;
                    }
                }
            }
            return commonIngredients;
        }
};

class RecipeBook {
    private:
        list<Meal*> mealsPointers;

    public:
        int numMeals;
        RecipeBook(string menu_path) {
            this->numMeals = 0;
            initializeFromTxt(menu_path);
        }

        void initializeFromTxt(string menu_path) {
            ifstream inputFile(menu_path);
            if (!inputFile.is_open()) {
                cout << "Unable to open file." << endl;
                return;
            }

            string mealName;
            vector<string> ingredients;
            vector<int> priorities;

            string line;
            int count = 0;
            while (getline(inputFile, line)) {
                if (line.empty()) continue;
                else if (line[0] == '-') {
                    size_t pos = line.find_last_of('(');
                    size_t prio = stoi(line.substr(pos + 1, 1));
                    ingredients.push_back(line.substr(2, pos - 3));
                    priorities.push_back(prio);
                } else {
                    if (!mealName.empty()) {
                        addMeal(mealName, ingredients, priorities);
                        mealName.clear();
                        ingredients.clear();
                        priorities.clear();
                    }
                    mealName = line;
                }
            }
            if (!mealName.empty()) addMeal(mealName, ingredients, priorities);

            inputFile.close();
        }

        void addMeal(string mealName, vector<string> ingredients, vector<int> priorities) {
            Ingredient* ingredientsList = generateIngredientList(ingredients.data(), priorities.data(), ingredients.size());
            Meal* meal = new Meal(mealName, ingredients.size(), ingredientsList);
            mealsPointers.push_back(meal);
            numMeals++;
        }

        Meal* getMeal(string name) {
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                if ((*it)->name == name) {
                    return *it;
                }
            }
            return NULL;
        }

        unordered_set<string> getIngredientList() {
            unordered_set<string> ingredientList;
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                for (int i = 0; i < (*it)->numIngredients; i++) {
                    ingredientList.insert((*it)->ingredients[i].name);
                }
            }
            return ingredientList;
        }

        vector<string> getMealList() {
            vector<string> mealList;
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                mealList.push_back((*it)->name);
            }
            return mealList;
        }

        int getCommonIngredients(string meal1, string meal2) {
            Meal* meal1Pointer = getMeal(meal1);
            Meal* meal2Pointer = getMeal(meal2);
            return meal1Pointer->numberCommonIngredients(meal2Pointer);
        }

        vector<string> getCommonIngredientsList(string meal1, string meal2) {
            Meal* meal1Pointer = getMeal(meal1);
            Meal* meal2Pointer = getMeal(meal2);
            return meal1Pointer->getCommonIngredients(meal2Pointer);
        }

        MealPriority* getMealPriorities() {
            MealPriority* priorities = new MealPriority[numMeals];
            int i = 0;
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                priorities[i].name = (*it)->name;
                priorities[i].priority = (*it)->getTotalPriority();
                i++;
            }
            return priorities;
        }

        void prioritizeMeals(vector<string> ingredientList) {
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                Meal meal = **it;
                for (int i = 0; i < ingredientList.size(); i++) {
                    meal.prioritize(ingredientList[i]);
                }
            }
        }

        priority_queue<MealPriority> generateSuggestionQueue() {
            priority_queue<MealPriority> suggestionQueue;
            MealPriority* priorities = getMealPriorities();
            for (int i = 0; i < numMeals; i++) {
                suggestionQueue.push(priorities[i]);
            }
            return suggestionQueue;
        }

        void print() {
            for (list<Meal*>::iterator it = mealsPointers.begin(); it != mealsPointers.end(); it++) {
                cout << (*it)->name << ":" << endl;
                for (int i = 0; i < (*it)->numIngredients; i++) {
                    cout << "- " << (*it)->ingredients[i].name << " " << (*it)->ingredients[i].priority << endl;
                }
            }
        }
};

class CommonIngredientMap {
private:
    vector<string> nodes; // Store node names
    vector<vector<pair<int, int>>> adj; // Adjacency list (vertex, weight)
        RecipeBook& recipes;

    public:
        CommonIngredientMap(RecipeBook& recipes) : recipes(recipes) {
            this->nodes = recipes.getMealList();
            adj.resize(nodes.size());
            initializeEdges();
        }

        // Function to add a node
        void addNode(string nodeName) {
            nodes.push_back(nodeName);
            adj.resize(nodes.size());
        }

    // Function to add an edge between nodes u and v with weight w
    void addEdge(string u, string v, int w) {
        int uIndex = getIndex(u);
        int vIndex = getIndex(v);
        adj[uIndex].push_back(make_pair(vIndex, w));
        adj[vIndex].push_back(make_pair(uIndex, w));
    }

    // Function to get the index of a node in the nodes vector
    int getIndex(string nodeName) {
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i] == nodeName) {
                return i;
            }
        }
        return -1; // Node not found
    }

    void initializeEdges() {
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                int commonIngredients = recipes.getCommonIngredients(nodes[i], nodes[j]);
                if (commonIngredients > 0) {
                    addEdge(nodes[i], nodes[j], commonIngredients);
                }
            }
        }
    }

    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> nextMeals(string currentMeal) {
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> nextMeals(cmp);
        int currentIndex = getIndex(currentMeal);
        for (const auto& edge : adj[currentIndex]) {
            pair<string, int> nextMeal = make_pair(nodes[edge.first], edge.second);
            nextMeals.push(nextMeal);
        }
        return nextMeals;
    }

    void print() {
        for (int i = 0; i < nodes.size(); ++i) {
            cout << "Adjacency list of node " << nodes[i] << ": ";
            for (const auto& edge : adj[i]) {
                cout << "(" << nodes[edge.first] << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    RecipeBook recipes("menu.txt");
    CommonIngredientMap ingredient_map(recipes);
    
    string current_meal = "Spaghetti Bolognese";
    
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> nextMeals = ingredient_map.nextMeals(current_meal);
    
    while (!nextMeals.empty()) {
        pair<string, int> nextMeal = nextMeals.top();
        nextMeals.pop();
        string mealName = nextMeal.first;
        vector<string> commonIngredients = recipes.getCommonIngredientsList(current_meal, mealName);
        
        cout << "Cooking " << mealName << " for next meal can reuse " << commonIngredients.size() << " ingredients: ";
        
        for (int j = 0; j < commonIngredients.size(); j++) {
            cout << commonIngredients[j] << ", ";
        }
        cout << endl;
    }
    

    return 0;
}