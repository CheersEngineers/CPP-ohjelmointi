#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// Kortin rakenne
struct Kortti {
    std::string maa;
    std::string pelikortti;
    int arvo;
};

// Korttipakan luominen
std::vector<Kortti> luoPakka() {
    std::vector<Kortti> pakka;
    std::string maat[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string pelikortit[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int arvot[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (const auto & maa : maat) {
        for (int i = 0; i < 13; ++i) {
            pakka.push_back({maa, pelikortit[i], arvot[i]});
        }
    }
    return pakka;
}

// Korttipakan sekoittaminen
void sekoitaPakka(std::vector<Kortti> & pakka) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pakka.begin(), pakka.end(), g);
}

// Korttien tulostaminen
void printKortti(const Kortti & Kortti) {
    std::cout << Kortti.pelikortti << " of " << Kortti.maa << " (" << Kortti.arvo << ")\n";
}

// Käden arvon laskeminen
int laskeKadenArvo(const std::vector<Kortti> & hand) {
    int arvo = 0;
    int AssanLuku = 0;
    for (const auto& Kortti : hand) {
        arvo += Kortti.arvo;
        if (Kortti.pelikortti == "Ace") {
            ++AssanLuku;
        }
    }
    while (arvo > 21 && AssanLuku > 0) {
        arvo -= 10;
        --AssanLuku;
    }
    return arvo;
}

// Pelaajan vuoro
bool pelaajanVuoro(std::vector<Kortti>& pakka, std::vector<Kortti>& pelaajanKasi) {
    while (true) {
        std::cout << "\n";
        std::cout << "Your hand:\n";
        for (const auto& Kortti : pelaajanKasi) {
            printKortti(Kortti);
        }
        int kadenArvo = laskeKadenArvo(pelaajanKasi);
        std::cout << "\n";
        std::cout << "Hand value: " << kadenArvo << "\n";
        if (kadenArvo > 21) {
            std::cout << "Bust! You lose.\n";
            return false;
        }

        std::cout << "\n";
        std::cout << "Do you want to hit (h) or stand (s)? ";
        char choice;
        std::cin >> choice;
        if (choice == 's') {
            break;
        } else if (choice == 'h') {
            pelaajanKasi.push_back(pakka.back());
            pakka.pop_back();
        }
    }
    return true;
}

// Jakajan vuoro
bool jakajanVuoro(std::vector<Kortti>& pakka, std::vector<Kortti>& jakajanKasi) {
    while (laskeKadenArvo(jakajanKasi) < 17) {
        jakajanKasi.push_back(pakka.back());
        pakka.pop_back();
    }
    int kadenArvo = laskeKadenArvo(jakajanKasi);
    std::cout << "Dealer's hand:\n";
    for (const auto& Kortti : jakajanKasi) {
        printKortti(Kortti);
    }
    std::cout << "Hand value: " << kadenArvo << "\n";
    return kadenArvo <= 21;
}

// BlackJack-pelin pääfunktio
int main() {
    char playAgain;
    do {
        std::vector<Kortti> pakka = luoPakka();
        sekoitaPakka(pakka);

        std::vector<Kortti> pelaajanKasi = {pakka.back()};
        pakka.pop_back();
        pelaajanKasi.push_back(pakka.back());
        pakka.pop_back();

        std::vector<Kortti> jakajanKasi = {pakka.back()};
        pakka.pop_back();
        jakajanKasi.push_back(pakka.back());
        pakka.pop_back();

        if (!pelaajanVuoro(pakka, pelaajanKasi)) {
            std::cout << "\n";
            std::cout << "Do you want to play again (y/n)? ";
            std::cin >> playAgain;
            continue;
        }

        if (!jakajanVuoro(pakka, jakajanKasi)) {
            std::cout << "Dealer busts! You win!\n";
            std::cout << "\n";
            std::cout << "Do you want to play again (y/n)? ";
            std::cin >> playAgain;
            continue;
        }

        int pelaajanArvo = laskeKadenArvo(pelaajanKasi);
        int jakajanArvo = laskeKadenArvo(jakajanKasi);

        if (pelaajanArvo > jakajanArvo) {
            std::cout << "\n";
            std::cout << "You win!\n";
            std::cout << "\n";
        } else if (pelaajanArvo < jakajanArvo) {
            std::cout << "\n";
            std::cout << "You lose.\n";
            std::cout << "\n";
        } else {
            std::cout << "\n";
            std::cout << "It's a tie!\n";
            std::cout << "\n";
        }

        std::cout << "\n";
        std::cout << "Do you want to play again (y/n)? ";
        std::cout << "\n";
        std::cin >> playAgain;
    } while (playAgain == 'y');

    return 0;
}
