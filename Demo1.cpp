/**
 * Demo program for Pandemic exercise - OperationsExpert role
 *
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "sources/Board.hpp"
#include "sources/City.hpp"
#include "sources/Color.hpp"
/* include main classes */
#include "sources/Board.hpp"
#include "sources/City.hpp"
#include "sources/Color.hpp"
#include "sources/Player.hpp"
/* include special skills players */
#include "sources/Researcher.hpp"
#include "sources/Scientist.hpp"
#include "sources/FieldDoctor.hpp"
#include "sources/GeneSplicer.hpp"
#include "sources/OperationsExpert.hpp"
#include "sources/Dispatcher.hpp"
#include "sources/Medic.hpp"
#include "sources/Virologist.hpp"

#include "sources/OperationsExpert.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>

using namespace std;
const map<City, Color> city_color {
        { City::Algiers, Color::Black },{ City::Atlanta, Color::Blue },{ City::Baghdad, Color::Black },{ City::Bangkok, Color::Red },
        { City::Beijing, Color::Red },{ City::Bogota, Color::Yellow },{ City::BuenosAires, Color::Yellow },{ City::Cairo, Color::Black },
        { City::Chennai, Color::Black },{ City::Chicago, Color::Blue },{ City::Delhi, Color::Black },{ City::Essen, Color::Blue },
        { City::HoChiMinhCity, Color::Red },{ City::HongKong, Color::Red },{ City::Istanbul, Color::Black },{ City::Jakarta, Color::Red },
        { City::Johannesburg, Color::Yellow },{ City::Karachi, Color::Black },{ City::Khartoum, Color::Yellow },{ City::Kinshasa, Color::Yellow },
        { City::Kolkata, Color::Black },{ City::Lagos, Color::Yellow },{ City::Lima, Color::Yellow },{ City::London, Color::Blue },
        { City::LosAngeles, Color::Yellow },{ City::Madrid, Color::Blue },{ City::Manila, Color::Red },{ City::MexicoCity, Color::Yellow },
        { City::Miami, Color::Yellow },{ City::Milan, Color::Blue },{ City::Montreal, Color::Blue },{ City::Moscow, Color::Black },
        { City::Mumbai, Color::Black },{ City::NewYork, Color::Blue },{ City::Osaka, Color::Red },{ City::Paris, Color::Blue },
        { City::Riyadh, Color::Black },{ City::SanFrancisco, Color::Blue },{ City::Santiago, Color::Yellow },{ City::SaoPaulo, Color::Yellow },
        { City::Seoul, Color::Red },{ City::Shanghai, Color::Red },{ City::StPetersburg, Color::Blue },{ City::Sydney, Color::Red },
        { City::Taipei, Color::Red },{ City::Tehran, Color::Black },{ City::Tokyo, Color::Red },{ City::Washington, Color::Blue }
};
const map<City, vector<City>> cities {
        { City::Algiers, {City::Madrid, City::Paris, City::Istanbul, City::Cairo } },
        { City::Atlanta, {City::Chicago, City::Miami, City::Washington } },
        { City::Baghdad, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi } },
        { City::Bangkok, {City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong } },
        { City::Beijing, {City::Shanghai, City::Seoul } },
        { City::Bogota, {City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires } },
        { City::BuenosAires, {City::Bogota, City::SaoPaulo } },
        { City::Cairo, {City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh } },
        { City::Chennai, {City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta } },
        { City::Chicago, {City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal } },
        { City::Delhi, {City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata } },
        { City::Essen, {City::London, City::Paris, City::Milan, City::StPetersburg } },
        { City::HoChiMinhCity, {City::Jakarta, City::Bangkok, City::HongKong, City::Manila } },
        { City::HongKong, {City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei } },
        { City::Istanbul, {City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow } },
        { City::Jakarta, {City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney } },
        { City::Johannesburg, {City::Kinshasa, City::Khartoum } },
        { City::Karachi, {City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi } },
        { City::Khartoum, {City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg } },
        { City::Kinshasa, {City::Lagos, City::Khartoum, City::Johannesburg } },
        { City::Kolkata, {City::Delhi, City::Chennai, City::Bangkok, City::HongKong } },
        { City::Lagos, {City::SaoPaulo, City::Khartoum, City::Kinshasa } },
        { City::Lima, {City::MexicoCity, City::Bogota, City::Santiago } },
        { City::London, {City::NewYork, City::Madrid, City::Essen, City::Paris } },
        { City::LosAngeles, {City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney } },
        { City::Madrid, {City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers } },
        { City::Manila, {City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney } },
        { City::MexicoCity, {City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota } },
        { City::Miami, {City::Atlanta, City::MexicoCity, City::Washington, City::Bogota } },
        { City::Milan, {City::Essen, City::Paris, City::Istanbul } },
        { City::Montreal, {City::Chicago, City::Washington, City::NewYork } },
        { City::Moscow, {City::StPetersburg, City::Istanbul, City::Tehran } },
        { City::Mumbai, {City::Karachi, City::Delhi, City::Chennai } },
        { City::NewYork, {City::Montreal, City::Washington, City::London, City::Madrid } },
        { City::Osaka, {City::Taipei, City::Tokyo } },
        { City::Paris, {City::Algiers, City::Essen, City::Madrid, City::Milan, City::London } },
        { City::Riyadh, {City::Baghdad, City::Cairo, City::Karachi } },
        { City::SanFrancisco, {City::LosAngeles, City::Chicago, City::Tokyo, City::Manila } },
        { City::Santiago, {City::Lima } },
        { City::SaoPaulo, {City::Bogota, City::BuenosAires, City::Lagos, City::Madrid } },
        { City::Seoul, {City::Beijing, City::Shanghai, City::Tokyo } },
        { City::Shanghai, {City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo } },
        { City::StPetersburg, {City::Essen, City::Istanbul, City::Moscow } },
        { City::Sydney, {City::Jakarta, City::Manila, City::LosAngeles } },
        { City::Taipei, {City::Shanghai, City::HongKong, City::Osaka, City::Manila } },
        { City::Tehran, {City::Baghdad, City::Moscow, City::Karachi, City::Delhi } },
        { City::Tokyo, {City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco } },
        { City::Washington, {City::Atlanta, City::NewYork, City::Montreal, City::Miami } }
};

City random_city() {
    size_t t = (size_t)rand() % 47;
    int i = 0;
    for(const auto& city: cities) {
        if(i == t) {
            return city.first;
        }
        i++;
    }
    return City::Algiers;
}
/* פונקציית עזר שמגרילה עיר כלשהי */
City random_city_different_than(City c) {
    City r = random_city();
    while((r = random_city()) == c){}
    return (City)r;
}
Color get_color(City c) {
    return city_color.at(c);
}

/* פונקציית עזר שמגרילה עיר  */
City random_city_colored(Color c) {
    while(true) {
        City r = random_city();
        if(city_color.at(r) == c) {
            return r;
        }
    }
    return City::Algiers;
}

/* פונקציית עזר המגרילה מספר מסוים של ערים בצבע נתון  */
set<City> pick_N_cities_colored(int N, Color c) {
    set<City> ans;
    while(ans.size() < N) {
        ans.insert(random_city_colored(c));
    }
    return ans;
}
const vector<City> all_cities {
        City::Algiers,City::Atlanta,City::Baghdad,City::Bangkok,City::Beijing,City::Bogota,City::BuenosAires,City::Cairo,City::Chennai,
        City::Chicago,City::Delhi,City::Essen,City::HoChiMinhCity,City::HongKong,City::Istanbul,City::Jakarta,City::Johannesburg,
        City::Karachi,City::Khartoum,City::Kinshasa,City::Kolkata,City::Lagos,City::Lima,City::London,City::LosAngeles,
        City::Madrid,City::Manila,City::MexicoCity,City::Miami,City::Milan,City::Montreal,City::Moscow,City::Mumbai,City::NewYork,
        City::Osaka,City::Paris,City::Riyadh,City::SanFrancisco,City::Santiago,City::SaoPaulo,City::Seoul,City::Shanghai,City::StPetersburg,
        City::Sydney,City::Taipei,City::Tehran,City::Tokyo,City::Washington
};

bool is_connected(City c1, City c2) {
    for(const auto& c: cities.at(c1)) {
        if(c == c2) return true;
    }
    return false;
}
City random_connected_city(City c) {
    size_t adjes = (size_t)rand() % (size_t)cities.at(c).size();
    return cities.at(c).at(adjes);
}

int iin = 0;
int main() {
    Board board;
    City city = random_city();
    OperationsExpert operationsExpert{board, city};
    Dispatcher dispatcher{board, city};
    Scientist scientist{board, city, 4};
    Researcher researcher{board, city};
    Medic medic{board, city};
    Virologist virologist{board, city};
    GeneSplicer geneSplicer{board, city};
    FieldDoctor fieldDoctor{board, city};
    Player *players[] = {&operationsExpert,
                         &dispatcher,
                         &scientist,
                         &researcher,
                         &medic,
                         &virologist,
                         &geneSplicer,
                         &fieldDoctor};

    /* מעבר אקראי בין ערים מחוברות ע"י נסיעה רגילה */
    for(int i = 0; i < 10; i++) {
        City c = random_city();
        /* אם העיר הבאה מחוברת לעיר הנוכחית - ניתן לבצע נסיעה רגילה */
        for(int i = 0; i < 10; i++) {
            Board b;
            City city = random_city();
            FieldDoctor player{b, city};
            if(iin == 200){
                cout <<"";
            }
            bool a = false;
            try {
                player.treat(city); //no disease cubes
            }
            catch (...) {
                a=true;
            }
            if(!a) {
                cout << "fuck";
            }

            /* מעבר רנדומלי בין הערים השונות בעזרת נסיעה רגילה */
            for(int j = 0; j < 20; j++) {
                city = random_connected_city(city);
                iin++;
                b[city] = 10;
                if(b[city] != 10){
                    cout<<"10 10 10 10 10 10 - j - "<< j<<" iin - "<< iin<< ", city-"<< city<< endl;
                }
                player.treat(city);
                if(b[city] != 9){
                    cout<<"9 9 9 9 9 9 9  - j - "<< j<<" iin - "<< iin<< ", city-"<< city<< endl;
                }
                player.drive(city);
            }
        }
    }
}
