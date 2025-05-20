#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>

std::vector<int> random_list(int n) {
    std::vector<int> list_data(n); 
    for (int i = 1; i <= n; i++) {
        list_data[i - 1] = i;
    }
    
    std::mt19937 random_engine(static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    ));
    std::shuffle(list_data.begin(), list_data.end(), random_engine);
    return list_data;
}

void DrawCurrentState(sf::RenderWindow& screen, const std::vector<int>& list_data, int a, int b) {
    screen.clear(sf::Color::Black);
    int n = list_data.size();
    if (n == 0) {
        screen.display();
        return;
    }

    float BarWidth = static_cast<float>(screen.getSize().x) / n;
     

    for (int i = 0; i < n; i++) {
        float normalized_height = static_cast<float>(list_data[i]) / n;
        float BarHeight = normalized_height * screen.getSize().y;
        if (BarHeight < 0) BarHeight = 0;

        sf::RectangleShape bar(sf::Vector2f(BarWidth, BarHeight));

        bar.setPosition({i * BarWidth, screen.getSize().y - BarHeight});
        if(i == a || i == b){
            bar.setFillColor(sf::Color::Yellow);
        }
        else{
            bar.setFillColor(sf::Color::White);
        }
        screen.draw(bar);
    }
    screen.display();
}


void bubble_sort_visualized(std::vector<int>& list_data, sf::RenderWindow& screen) {
    bool swapped_in_pass;
    int n = list_data.size();
    for (int i = 0; i < n - 1; i++) {
        swapped_in_pass = false;
        for (int j = 0; j < n - 1 - i; j++) {

            while (const auto event = screen.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    screen.close();
                    return;         
                }
                if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close();
                    return;
                }
            }
            }
            if (!screen.isOpen()) return;

            DrawCurrentState(screen, list_data, i, j);

            sf::sleep(sf::microseconds(1));

            if (list_data[j] > list_data[j + 1]) {
                std::swap(list_data[j], list_data[j + 1]);
                swapped_in_pass = true;
            }
        }
        if (!swapped_in_pass && i > 0) { 
            break;
        }
    }

    for(int i = 0; i < n; i++){
        sf::sleep(sf::microseconds(50));
        DrawCurrentState(screen, list_data, i, -1);
    }
    
    if (screen.isOpen()) {
        DrawCurrentState(screen, list_data, -1, -1);
    }
}

int main() {

    int n = 200;
    std::vector<int> my_list = random_list(n); 

   
    sf::RenderWindow screen(sf::VideoMode({1440, 900}), "Sorting",sf::Style::None, sf::State::Fullscreen);
    
    bubble_sort_visualized(my_list, screen);
    screen.setFramerateLimit(60); 

    while (screen.isOpen()) {

        while (const auto event = screen.pollEvent()) { 
            if (event->is<sf::Event::Closed>()) {
                screen.close();
            }
            
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R) {
                    my_list = random_list(n);
                    bubble_sort_visualized(my_list, screen); 
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close();
                    return 0;
                }
            }
        }

        DrawCurrentState(screen, my_list, -1, -1);
    }

    return 0;
}