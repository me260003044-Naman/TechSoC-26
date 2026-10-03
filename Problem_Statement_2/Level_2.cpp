#include<iostream>
#include <array>
#include <string>
#include<map>
#include<ctime>
using namespace std;

struct Move
{
    string move_name;
    int move_power;
};

struct elementPair
{
    string strong;
    string weak;
};



class Bender{
    private:
        const array<elementPair,4> element_pair={{{"Water","Fire"},{"Fire","Air"},{"Air","Earth"},{"Earth","Water"}}};

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

        void attack(Bender& defender,int move_index,int& ch,int& sh){
            cout<<name<<" used "<<moves[move_index].move_name<<"!\n";
            double multiplier=1;
            for(elementPair ep:element_pair){
                if(element==ep.strong && defender.element==ep.weak){cout<<"Super Effective! ("<<ep.strong<<" is strong against "<<ep.weak<<")"<<endl;multiplier=2;sh++;break;}
                if(element==ep.weak && defender.element==ep.strong){cout<<"Not very effective... ("<<ep.weak<<" is weak against "<<ep.strong<<")"<<endl;multiplier=0.5;break;}
            }
            srand(time(0));
            if(rand()%10==3){cout<<"Critical Hit!\n";multiplier=multiplier*2;ch++;}
            int base_damage=moves[move_index].move_power*attack_power/defender.defence;
            int damage=multiplier*base_damage;
            cout<<defender.name<<" took "<<damage<<" damage!\n";
            defender.hp-=damage;
            if(defender.hp<0)defender.hp=0;
            cout<<defender.name<<" HP: "<<defender.hp<<"/"<<defender.max_hp<<endl<<endl;
        }
        void check_fainted(){
            if(hp==0)cout<<name<<" fainted: True";
            else cout<<name<<" fainted: False";
            cout<<"\n";
        }
        //friend class
        friend class Duel;
        
        //getter
        int getSpeed(){
            return speed;
        }
        int getHp(){
            return hp;
        }
};

class Duel{
    private:
    int turn=0;
    int ch=0;
    int sh=0;
    public:
    Duel(Bender& p1,Bender& p2){
        //game start
        cout<<"=== DUEL BEGINS! ===\n";
        cout<<p1.name<<" ("<<p1.element<<", HP: "<<p1.hp<<"/"<<p1.max_hp<<") vs "<<p2.name<<" ("<<p2.element<<", HP: "<<p2.hp<<"/"<<p2.max_hp<<")\n";
        if(p1.getSpeed()>p2.getSpeed()){
            do
            {
                turn++;
                int move_input;
                cout<<"Turn "<<turn<<": "<<p1.name<<" goes first!\n";
                cout<<"Chose your move \n";
                for(int i=0;i<4;i++){
                    cout<<p1.moves[i].move_name<<" = "<<i<<"   ";
                }
                cout<<"\n";
                cin>>move_input;
                p1.attack(p2,move_input,ch,sh);
                if(p2.hp==0)break;
                
                turn++;
                cout<<"Turn "<<turn<<": "<<p2.name<<" strikes back\n";
                cout<<"Chose your move \n";
                for(int i=0;i<4;i++){
                    cout<<p2.moves[i].move_name<<" = "<<i<<"\t";
                }
                cout<<"\n";
                cin>>move_input;
                p2.attack(p1,move_input,ch,sh);
                if(p1.hp==0)break;
            } while (true);
            
        }
        else if(p1.getSpeed()<=p2.getSpeed()){
            do
            {
                turn++;
                int move_input;
                cout<<"Turn "<<turn<<": "<<p2.name<<" goes first\n";
                cout<<"Chose your move \n";
                for(int i=0;i<3;i++){
                    cout<<p2.moves[i].move_name<<" = "<<i<<"\t";
                }
                cout<<"\n";
                cin>>move_input;
                p2.attack(p1,move_input,ch,sh);
                if(p1.hp==0)break;
                
                turn++;
                cout<<"Turn "<<turn<<": "<<p1.name<<" strikes back\n";
                cout<<"Chose your move \n";
                for(int i=0;i<3;i++){
                    cout<<p1.moves[i].move_name<<" = "<<i<<"\t";
                }
                cout<<"\n";
                cin>>move_input;
                p1.attack(p2,move_input,ch,sh);
                if(p2.hp==0)break;
            } while (true);
            
        }
        if(p1.hp==0){
            cout<<p1.name<<" fainted!\n"<<p2.name<<" won the duel!!\n\n";
            cout<<"Duel Summary: \n- Winner: "<<p2.name<<"\n- Turns: "<<turn<<"\n- Critical Hit: "<<ch<<"\nSuper Effective Hits: "<<sh;
        }
        if(p2.hp==0){
            cout<<p2.name<<" fainted!\n"<<p1.name<<" won the duel!!\n\n";
            cout<<"Duel Summary: \n- Winner: "<<p1.name<<"\n- Turns: "<<turn<<"\n- Critical Hit: "<<ch<<"\nSuper Effective Hits: "<<sh;
        }
    }
    
};


int main(){
    Bender kael("Kael", "Fire", 100, 58, 38, 88,{{{"Ember Slash", 40},{"Quick Jab", 30},{"Focus", 0},{"Flame Surge", 70}}});
    Bender mira("Mira", "Water", 92, 50, 45, 60,{{{"Water Whip", 35},{"Tide Push", 25},{"Mist Veil", 0},{"Tidal Wave", 60}}});
    Duel duel(kael,mira);
    
    return 0;
}