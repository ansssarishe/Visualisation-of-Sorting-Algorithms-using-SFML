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
            bar.setFillColor(sf::Color::Red);
        }
        else{
            bar.setFillColor(sf::Color::White);
        }
        screen.draw(bar);
    }
    screen.display();
}

int partition(std::vector<int>& list_data, int low, int high, sf::RenderWindow& screen){
    int pivot = list_data[low];
    int j = low;
    for(int i = low + 1; i <= high; i++){
        while (const auto event = screen.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { screen.close(); return -1; }
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close(); return -1;
                }
            }
        }
        if (!screen.isOpen()) return -1;

        DrawCurrentState(screen, list_data, j, i);


        if(list_data[i] < pivot){
            j++;
            std::swap(list_data[i], list_data[j]);
        }
    }
    std::swap(list_data[j], list_data[low]);
    
    return j;
}

void QuickSort_visualized(std::vector<int>& list_data, int low, int high, sf::RenderWindow& screen){
    while (const auto event = screen.pollEvent()) {
        if (event->is<sf::Event::Closed>()) { screen.close(); return; }
        if (event->is<sf::Event::KeyPressed>()) {
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                screen.close(); return;
            }
        }
    }
    if (!screen.isOpen()) return;
    
    if(low < high){
        int pivot_index = partition(list_data, low, high, screen);

        if (!screen.isOpen() || pivot_index == -1) return;

        QuickSort_visualized(list_data, low, pivot_index - 1, screen);
        QuickSort_visualized(list_data, pivot_index + 1, high, screen);
    }

}

void merge(std::vector<int>& list_data, int left, int mid, int right, sf::RenderWindow& screen){
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    std::vector<int> leftArr(leftSize);
    std::vector<int> rightArr(rightSize);

    
    for(int i = 0; i < leftSize; i++){
        leftArr[i] = list_data[left + i];
    }
    for(int i = 0; i < rightSize; i++){
        rightArr[i] = list_data[mid + 1 + i];
    }

    int indexOfLeft = 0;      
    int indexOfRight = 0;     
    int indexOfMerged = left; 

    
    while(indexOfLeft < leftSize && indexOfRight < rightSize){
        
        while (const auto event = screen.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { screen.close(); return; }
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close(); return;
                }
            }
        }
        if (!screen.isOpen()) return;

        
        DrawCurrentState(screen, list_data, left + indexOfLeft, mid + 1 + indexOfRight);
        //DrawCurrentState(screen, list_data, indexOfLeft, indexOfRight);

        if(leftArr[indexOfLeft] <= rightArr[indexOfRight]){
            list_data[indexOfMerged] = leftArr[indexOfLeft];
            indexOfLeft++;
        }
        else{
            list_data[indexOfMerged] = rightArr[indexOfRight];
            indexOfRight++;
        }
        indexOfMerged++;
    }

    

    
    while(indexOfLeft < leftSize){
        
        while (const auto event = screen.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { screen.close(); return; }
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close(); return;
                }
            }
        }
        if (!screen.isOpen()) return;

        
        DrawCurrentState(screen, list_data, left + indexOfLeft, -1);
        

        list_data[indexOfMerged] = leftArr[indexOfLeft];
        indexOfLeft++;
        indexOfMerged++;
    }

    
    while(indexOfRight < rightSize){
        
        while (const auto event = screen.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { screen.close(); return; }
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    screen.close(); return;
                }
            }
        }
        if (!screen.isOpen()) return;

        DrawCurrentState(screen, list_data, -1, mid + 1 + indexOfRight); 

        list_data[indexOfMerged] = rightArr[indexOfRight];
        indexOfRight++;
        indexOfMerged++;
    }
}

void mergeSortRecursive(std::vector<int>& list_data, int left, int right, sf::RenderWindow& screen) {
    while (const auto event = screen.pollEvent()) {
        if (event->is<sf::Event::Closed>()) { screen.close(); return; }
        if (event->is<sf::Event::KeyPressed>()) {
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                screen.close(); return;
            }
        }
    }
    if (!screen.isOpen()) return;

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2; 

    mergeSortRecursive(list_data, left, mid, screen);

    mergeSortRecursive(list_data, mid + 1, right, screen);

    merge(list_data, left, mid, right, screen);

    DrawCurrentState(screen, list_data, left, right);
}

void merge_sort_visualized(std::vector<int>& list_data, sf::RenderWindow& screen) {
    mergeSortRecursive(list_data, 0, list_data.size() - 1, screen);

    DrawCurrentState(screen, list_data, 0, list_data.size() - 1);
}

void insertion_sort_visualized(std::vector<int>& list_data, sf::RenderWindow& screen){
    int n = list_data.size();
    for(int i = 1; i < n; i++){
        int j = i;
        while(j > 0 && list_data[j - 1] > list_data[j]){
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

            std::swap(list_data[j], list_data[j - 1]);
            j--;
        }
    }
}

void selection_sort_visualized(std::vector<int>& list_data, sf::RenderWindow& screen){
    int n = list_data.size();
    for(int i = 0; i < n; i++){
        int min = i;
        for(int j = i; j < n; j++){
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

            if(list_data[j] < list_data[min]) min = j;
            DrawCurrentState(screen, list_data, i, j);
        }
        std::swap(list_data[i], list_data[min]);
    }
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


            if (list_data[j] > list_data[j + 1]) {
                std::swap(list_data[j], list_data[j + 1]);
                swapped_in_pass = true;
            }
        }
        if (!swapped_in_pass && i > 0) { 
            break;
        }
    }

    
    if (screen.isOpen()) {
        DrawCurrentState(screen, list_data, -1, -1);
    }
}

int main() {
    int n;
    int sorting_choice;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    std::cout << "Select algorithm: \n1)Bubble Sort \n2)Selection Sort\n3)Insertion Sort\n4)Merge Sort\n5)Quick Sort\nChoice: ";
    std::cin >> sorting_choice;

    std::vector<int> my_list = random_list(n); 

   
    sf::RenderWindow screen(sf::VideoMode({1440, 900}), "Sorting",sf::Style::None, sf::State::Fullscreen);
    screen.setFramerateLimit(100);
    auto start = std::chrono::high_resolution_clock::now(); 

    switch(sorting_choice){
        case 1:
            bubble_sort_visualized(my_list, screen);
            break;
        case 2:
            selection_sort_visualized(my_list, screen);
            break;
        case 3:
            insertion_sort_visualized(my_list, screen);
            break;
        case 4:
            merge_sort_visualized(my_list, screen);
            break;
        case 5:
            QuickSort_visualized(my_list, 0, n - 1, screen);
            break;
    }

    for(int i = 0; i <= n; i++){
        DrawCurrentState(screen, my_list, i, -1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    
    //bubble_sort_visualized(my_list, screen);
    //selection_sort_visualized(my_list, screen);

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

        //DrawCurrentState(screen, my_list, -1, -1);
    }

    return 0;
}