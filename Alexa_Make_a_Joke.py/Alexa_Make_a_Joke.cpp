#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Joke {
    string question;
    string answer;
};

class JokeStudio {
private:
    vector<Joke> jokes;
    vector<size_t> favourites;
    mt19937 randomEngine{random_device{}()};

    string readText(const string& prompt) const {
        cout << prompt;
        string value;
        getline(cin, value);
        return value;
    }

    void loadJokes() {
        const array<string, 3> files = {
            "Alexa Make a Joke/randomJokes.txt",
            "S1-Programming-Skills-Portfolio/Alexa Make a Joke/randomJokes.txt",
            "randomJokes.txt"
        };

        for (const auto& path : files) {
            ifstream input(path);
            if (!input) continue;

            string line;
            while (getline(input, line)) {
                const auto separator = line.find('?');
                if (separator == string::npos) continue;

                string question = line.substr(0, separator + 1);
                string answer = line.substr(separator + 1);

                if (!question.empty() && !answer.empty())
                    jokes.push_back({question, answer});
            }

            if (!jokes.empty()) return;
        }

        jokes = {
            {"Why did the chicken cross the road?", "To get to the other side."},
            {"What happens if you boil a clown?", "You get a laughing stock."},
            {"Why did the developer go broke?", "Because they used up all their cache."},
            {"Why should you wear glasses in maths class?", "Because it helps with division."},
            {"What do you call a bear with no teeth?", "A gummy bear."}
        };
    }

    void loadFavourites() {
        ifstream input("joke_favourites.txt");
        size_t index;
        while (input >> index) {
            if (index < jokes.size()) favourites.push_back(index);
        }
    }

    void saveFavourites() const {
        ofstream output("joke_favourites.txt");
        for (const auto index : favourites) output << index << '\n';
    }

    void displayJoke(size_t index) const {
        cout << "\n" << jokes[index].question << "\n"
             << jokes[index].answer << "\n";
    }

    void randomJoke() {
        if (jokes.empty()) {
            cout << "No jokes are available.\n";
            return;
        }

        uniform_int_distribution<size_t> distribution(0, jokes.size() - 1);
        const size_t index = distribution(randomEngine);
        displayJoke(index);

        if (find(favourites.begin(), favourites.end(), index) == favourites.end()) {
            const string choice = readText("Save this joke as a favourite? (y/n): ");
            if (choice == "y" || choice == "Y") {
                favourites.push_back(index);
                saveFavourites();
                cout << "Favourite saved.\n";
            }
        }
    }

    void browseJokes() const {
        for (size_t i = 0; i < jokes.size(); ++i)
            cout << i + 1 << ". " << jokes[i].question << '\n';
        cout << "\nJokes available: " << jokes.size() << '\n';
    }

    void searchJokes() const {
        const string query = readText("Enter a keyword: ");
        size_t matches = 0;

        for (size_t i = 0; i < jokes.size(); ++i) {
            string content = jokes[i].question + " " + jokes[i].answer;
            string searchable = content;
            transform(searchable.begin(), searchable.end(), searchable.begin(),
                [](unsigned char c) { return static_cast<char>(tolower(c)); });

            string term = query;
            transform(term.begin(), term.end(), term.begin(),
                [](unsigned char c) { return static_cast<char>(tolower(c)); });

            if (searchable.find(term) != string::npos) {
                displayJoke(i);
                ++matches;
            }
        }

        cout << matches << " matching joke(s) found.\n";
    }

    void addJoke() {
        string question = readText("Enter the joke question: ");
        string answer = readText("Enter the punchline: ");

        if (question.empty() || answer.empty()) {
            cout << "Both fields are required.\n";
            return;
        }

        if (question.back() != '?') question += '?';
        jokes.push_back({question, answer});
        cout << "Joke added for this session.\n";
    }

    void showFavourites() const {
        if (favourites.empty()) {
            cout << "No favourites have been saved.\n";
            return;
        }

        for (size_t i = 0; i < favourites.size(); ++i) {
            cout << "\nFavourite " << i + 1 << '\n';
            displayJoke(favourites[i]);
        }
    }

public:
    JokeStudio() {
        loadJokes();
        loadFavourites();
    }

    void run() {
        while (true) {
            cout << "\n========== ALEXA JOKE STUDIO ==========\n"
                 << "1. Tell a random joke\n"
                 << "2. Browse all jokes\n"
                 << "3. Search jokes\n"
                 << "4. Add a joke\n"
                 << "5. View favourites\n"
                 << "6. Exit\n";

            int choice;
            cout << "Select an option: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: randomJoke(); break;
                case 2: browseJokes(); break;
                case 3: searchJokes(); break;
                case 4: addJoke(); break;
                case 5: showFavourites(); break;
                case 6: return;
                default: cout << "Choose an option from 1 to 6.\n";
            }
        }
    }
};

int main() {
    JokeStudio application;
    application.run();
    return 0;
}




