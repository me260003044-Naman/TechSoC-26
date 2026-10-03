#include<iostream>
#include <array>
#include <string>


using namespace std;

struct Move
{
    string move_name;
    int move_power;
};


class Bender{
    private:
        string name;
        string element;
        int hp;
        int max_hp;
        int attack_power;
        int defence;
        int speed;
        array<Move,4> moves;
    
    public:
        Bender(string n,string e,int h,int ap,int d,int s,array<Move,4> m):name(n),element(e),hp(h),max_hp(h),attack_power(ap),defence(d),speed(s),moves(m){}
        void display_stats(){
            cout<<name<<" ("<<element<<") - "<<"HP: "<<hp<<"/"<<max_hp<<", Attack: "<<attack_power<<", Defence: "<<defence<<", Speed: "<<speed<<"\n";
            cout<<"Moves:";
            for(int i=0;i<4;i++){
                cout<<" "<<moves[i].move_name<<" ("<<moves[i].move_power<<"),";
            }
            cout<<"\n\n";
        }

        void attack(Bender& defender,int move_index){
            int damage=moves[move_index].move_power*attack_power/defender.defence;
            cout<<name<<" used "<<moves[move_index].move_power<<"!\n";
            cout<<defender.name<<" took "<<damage<<" damage!\n\n";
            defender.hp-=damage;
            if(defender.hp<0)defender.hp=0;
        }
        void check_fainted(){
            if(hp==0)cout<<name<<" fainted: True";
            else cout<<name<<" fainted: False";
            cout<<"\n";
        }
};



int main(){
    Bender kael("Kael", "Fire", 100, 58, 38, 88,{{{"Ember Slash", 40},{"Quick Jab", 30},{"Focus", 0},{"Flame Surge", 70}}});
    Bender mira("Mira", "Water", 92, 50, 45, 60,{{{"Water Whip", 35},{"Tide Push", 25},{"Mist Veil", 0},{"Tidal Wave", 60}}});



    kael.display_stats();
    mira.display_stats();

    kael.attack(mira,3);
    kael.attack(mira,3);
    mira.display_stats();
    mira.check_fainted();
}