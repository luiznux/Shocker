#include "controller.h"
#include "parser.h"
#include <map>
#include "vinput.h"


void treat_trigger_event(int id, Trigger_Event te, map<int, string> key_map, Vinput &v);
void treat_stick_event(int id, Stick_Event se, map<int, string> key_map, Vinput &v);


int main () {
    Vinput virtualkeyboard;
    Parser p;
    map<int, string> key_map = p.get_key_maps("../profiles/profile1.pf");
    Controller com;
    queue<void *> events;
    string events_name[15] = {
            "SQUARE", "TRIANGLE", "CIRCLE", "X", "L1", "L3", "R1", "R3", "OPT", "SHARE", "L2", "R2", "LEFT_B", "L3_M",
            "R3_M"};
    while (true) {
        this_thread::sleep_for(chrono::microseconds(200));
        events = com.get_events();
        while (!events.empty()) {
            Event e = *(Event *) events.front();
            int id = e.get_id();
            if (id < 10) {
                cout << "<Event " << events_name[id] << ">" << "KEY: " << key_map[id] << endl;
                virtualkeyboard.key_press(key_map[id]);
            } else if (10 <= id && id <= 12) {
                cout << "<Trigger Event " << events_name[id] << ">";
                Trigger_Event te = *(Trigger_Event *) events.front();
                treat_trigger_event(id, te, key_map, virtualkeyboard);
            } else {
                cout << "<Stick Event " << events_name[id] << ">";
                Stick_Event se = *(Stick_Event *) events.front();
                treat_stick_event(id, se, key_map, virtualkeyboard);
            }

            events.pop();
        }
    }
    return 0;
}

void treat_trigger_event(int id, Trigger_Event te, map<int, string> key_map, Vinput &v){
    if(id == LEFT_B){
        if(te.get_value() == 7) {
            cout << " Key: " << key_map[LEFT_BU] << " Key: " << key_map[LEFT_BL] << endl;
            v.key_press(key_map[LEFT_BU]);
            v.key_press(key_map[LEFT_BL]);
        }
        else if(te.get_value() == 6) {
            cout << " Key: " << key_map[LEFT_BL] << endl;
            v.key_press(key_map[LEFT_BU]);
        }
        else if(te.get_value() == 5) {
            cout << " Key: " << key_map[LEFT_BD] << " Key: " << key_map[LEFT_BL]<< endl;
            v.key_press(key_map[LEFT_BD]);
            v.key_press(key_map[LEFT_BL]);
        }
        else if(te.get_value() == 4) {
            cout << " Key: " << key_map[LEFT_BD] << endl;
            v.key_press(key_map[LEFT_BD]);
        }
        else if(te.get_value() == 3) {
            cout << " Key: " << key_map[LEFT_BD] << " Key: " << key_map[LEFT_BR] << endl;
            v.key_press(key_map[LEFT_BD]);
            v.key_press(key_map[LEFT_BR]);
        }
        else if(te.get_value() == 2) {
            cout << " Key: " << key_map[LEFT_BR] << endl;
            v.key_press(key_map[LEFT_BR]);
        }
        else if(te.get_value() == 1) {
            cout << " Key: " << key_map[LEFT_BU] << " Key: " << key_map[LEFT_BR] << endl;
            v.key_press(key_map[LEFT_BU]);
            v.key_press(key_map[LEFT_BR]);
        }
        else {
            cout << " Key: " << key_map[LEFT_BU] << endl;
            v.key_press(key_map[LEFT_BU]);
        }
    }
    else {
        cout << "Value: " << (int) te.get_value() << "KEY: " << key_map[id] << endl;
        v.key_press(key_map[id]);
    }

}

void treat_stick_event(int id, Stick_Event se, map<int, string> key_map, Vinput &v){
    if (se.get_y() > 10) {
        cout << " Y: " << (int) se.get_y();
        if (se.is_up()) {
            if (id == R3_M) {
                cout << " Key: " << key_map[R3_MU] << endl;
                v.key_press(key_map[R3_MU]);
            }
            else{
                cout << " Key: " << key_map[L3_MU] << endl;
                v.key_press(key_map[L3_MU]);
            }
        } else {
            if (id == R3_M){
                cout << " Key: " << key_map[R3_MD]<< endl ;
                v.key_press(key_map[R3_MD]);
            }
            else{
                cout << " Key: " << key_map[L3_MD]<< endl;
                v.key_press(key_map[L3_MD]);
            }
        }
    }
    if (se.get_x() > 10) {
        cout << " X: " << (int)se.get_x();
        if (se.is_right()) {
            if (id == R3_M) {
                cout << " Key: " << key_map[R3_MR]<< endl;
                v.key_press(key_map[R3_MR]);
            }
            else{
                cout << " Key: " << key_map[L3_MR]<< endl;
                v.key_press(key_map[L3_MR]);
            }
        } else {
            if (id == R3_M){
                cout << " Key: " << key_map[R3_ML]<< endl;
                v.key_press(key_map[R3_ML]);
            }
            else {
                cout << " Key: " << key_map[L3_ML]<< endl;
                v.key_press(key_map[L3_ML]);
            }
        }
    }

}
