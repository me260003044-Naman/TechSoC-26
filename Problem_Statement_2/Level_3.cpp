#include<iostream>
#include <array>
#include <string>
#include<map>
#include<ctime>
#include<vector>

using namespace std;

struct Move
{
    string move_name;
    int move_power;
    string effect="nothing";
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

        int turn_buried=0,turn_frozen=0,turn_burn=0;

        int duel_index;
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
            srand(time(0));
            cout<<name<<" used "<<moves[move_index].move_name<<"!\n";
        if(moves[move_index].effect=="burn"){defender.turn_burn=4;cout<<defender.name<<" is now burning! (4 turns remaining)\n";}
            if(moves[move_index].effect=="frozen"){defender.turn_frozen=3;cout<<defender.name<<" is now frozen! (3 turns remaining)\n";}
            if(moves[move_index].effect=="buried"){defender.turn_buried=2+rand()%3;cout<<defender.name<<" is now burried! ("<<defender.turn_buried<<" turns remaining)\n";}

            double multiplier=1;
            for(elementPair ep:element_pair){
                if(element==ep.strong && defender.element==ep.weak){cout<<"Super Effective! ("<<ep.strong<<" is strong against "<<ep.weak<<")"<<endl;multiplier=2;sh++;break;}
                if(element==ep.weak && defender.element==ep.strong){cout<<"Not very effective... ("<<ep.weak<<" is weak against "<<ep.strong<<")"<<endl;multiplier=0.5;break;}
            }
            srand(time(0));
            if(rand()%10==3){cout<<"Critical Hit!\n";multiplier=multiplier*2;ch++;}
            int base_damage=moves[move_index].move_power*attack_power/defender.defence;
            int damage=(multiplier*base_damage);
            cout<<defender.name<<" took "<<damage<<" damage!\n";
            if(defender.turn_burn!=0){
                cout<<"Burning "<<defender.name<<" for "<<max_hp/10<<"!";
                turn_burn--;
                defender.hp-=defender.max_hp/10;
            }
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
        friend class AI_Duel;
        friend class Tournament;
        
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
    int winner_index;
    Duel(Bender& p1,Bender& p2){
        //game start
        cout<<p1.name<<" ("<<p1.element<<", HP: "<<p1.hp<<"/"<<p1.max_hp<<") vs "<<p2.name<<" ("<<p2.element<<", HP: "<<p2.hp<<"/"<<p2.max_hp<<")\n";
        if(p1.getSpeed()>p2.getSpeed()){
            do
            {   
                turn++;
                int move_input;
                if(p1.turn_buried!=0){
                    cout<<p1.name<<" is buried rn and cannot move\n";
                    cout<<"Buried duration: "<<--p1.turn_buried<<" turns remaining\n";
                }
                else if(p1.turn_frozen!=0 && rand()%2==0){
                    cout<<p1.name<<" is frozen rn and cannot move this time\n";
                    cout<<"Frozen duration: "<<--p1.turn_frozen<<" turns remaining\n";
                }
                else{
                    cout<<"Turn "<<turn<<": "<<p1.name<<" goes first!\n";
                    cout<<"Chose your move \n";
                    for(int i=0;i<4;i++){
                        cout<<p1.moves[i].move_name<<" = "<<i<<"   ";
                    }
                    cout<<"\n";
                    cin>>move_input;
                    p1.attack(p2,move_input,ch,sh);
                    if(p2.hp==0)break;
                }
                
                if(p1.turn_buried!=0){
                    cout<<p1.name<<" is buried rn and cannot move\n";
                    cout<<"Buried duration: "<<--p1.turn_buried<<" turns remaining\n";
                }
                else if(p1.turn_frozen!=0 && rand()%2==0){
                    cout<<p1.name<<" is frozen rn and cannot move this time\n";
                    cout<<"Frozen duration: "<<--p1.turn_frozen<<" turns remaining\n";
                }else{
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
                }
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
            winner_index=p2.duel_index;
        }
        if(p2.hp==0){
            cout<<p2.name<<" fainted!\n"<<p1.name<<" won the duel!!\n\n";
            cout<<"Duel Summary: \n- Winner: "<<p1.name<<"\n- Turns: "<<turn<<"\n- Critical Hit: "<<ch<<"\nSuper Effective Hits: "<<sh;
            winner_index=p1.duel_index;
        }
    }
    friend class Tournament;
};

class AI_Duel{
    private:
    int turn=0;
    int ch=0;
    int sh=0;

    public:
    AI_Duel(Bender& p,Bender& ai){
        //game start
        cout<<"=== AI DUEL BEGINS! ===\n";
        cout<<p.name<<" ("<<p.element<<", HP: "<<p.hp<<"/"<<p.max_hp<<") vs "<<ai.name<<" ("<<ai.element<<", HP: "<<ai.hp<<"/"<<ai.max_hp<<")\n";
        if(p.getSpeed()>ai.getSpeed()){
            do
            {   
                turn++;
                int move_input;
                if(p.turn_buried!=0){
                    cout<<p.name<<" is buried rn and cannot move\n";
                    cout<<"Buried duration: "<<--p.turn_buried<<"\n";
                }
                else if(p.turn_frozen!=0 && rand()%2==0){
                    cout<<p.name<<" is frozen rn and cannot move this time\n";
                    cout<<"Frozen duration: "<<--p.turn_frozen<<" turns remaining\n";
                }
                else{
                    cout<<"Turn "<<turn<<": "<<p.name<<" goes first!\n";
                    cout<<"Chose your move \n";
                    for(int i=0;i<4;i++){
                        cout<<p.moves[i].move_name<<" = "<<i<<"   ";
                    }
                    cout<<"\n";
                    cin>>move_input;
                    p.attack(ai,move_input,ch,sh);
                    if(ai.hp==0)break;
                }
                
                if(ai.turn_buried!=0){
                    cout<<ai.name<<" is buried rn and cannot move\n";
                    cout<<"Buried duration: "<<--ai.turn_buried<<" turns remaining\n";
                }
                else if(ai.turn_frozen!=0 && rand()%2==0){
                    cout<<ai.name<<" is frozen rn and cannot move this time\n";
                    cout<<"Frozen duration: "<<--ai.turn_frozen<<" turns remaining\n";
                }else{
                    if(ai.hp>3*ai.max_hp/10 || p.turn_buried!=0 || p.turn_burn!=0 || p.turn_frozen!=0){
                        do
                        {
                            move_input=rand()%4;
                        } while (move_input==1);
                        
                    }
                    else{
                        move_input=1;
                    }
                    turn++;
                    cout<<"Turn "<<turn<<": "<<ai.name<<" strikes back\n";
                    cout<<"AI Analysing:\n";
                    
                    ai.attack(p,move_input,ch,sh);
                    if(p.hp==0)break;
                }
            } while (true);
            
        }
        else if(p.getSpeed()<=ai.getSpeed()){
            do
            {
                turn++;
                int move_input;
                cout<<"Turn "<<turn<<": "<<ai.name<<" goes first\n";
                if(ai.hp>3*ai.max_hp/10 || p.turn_buried!=0 || p.turn_burn!=0 || p.turn_frozen!=0){
                        do
                        {
                            move_input=rand()%4;
                        } while (move_input==1);
                        
                    }
                    else{
                        move_input=1;
                    }
                ai.attack(p,move_input,ch,sh);
                if(p.hp==0)break;
                
                turn++;
                cout<<"Turn "<<turn<<": "<<p.name<<" strikes back\n";
                cout<<"Chose your move \n";
                for(int i=0;i<3;i++){
                    cout<<p.moves[i].move_name<<" = "<<i<<"\t";
                }
                cout<<"\n";
                cin>>move_input;
                p.attack(ai,move_input,ch,sh);
                if(ai.hp==0)break;
            } while (true);
            
        }
        if(p.hp==0){
            cout<<p.name<<" fainted!\n"<<ai.name<<" won the duel!!\n\n";
            cout<<"Duel Summary: \n- Winner: "<<ai.name<<"\n- Turns: "<<turn<<"\n- Critical Hit: "<<ch<<"\nSuper Effective Hits: "<<sh;
        }
        if(ai.hp==0){
            cout<<ai.name<<" fainted!\n"<<p.name<<" won the duel!!\n\n";
            cout<<"Duel Summary: \n- Winner: "<<p.name<<"\n- Turns: "<<turn<<"\n- Critical Hit: "<<ch<<"\nSuper Effective Hits: "<<sh;
        }
    }
    
};

class Tournament{
    private:
        int Tsh=0;
        int Tch=0;
    public:
        Tournament(vector<Bender> participants,string tournameName){
            for(int i=0;i<participants.size();i++){
                participants[i].duel_index=i;
            }
            cout<<"==="<<tournameName<<"===\n"<<"Participants: "<<participants.size()<<" Benders\n\n";
            cout<<"===TOURNAMENT BRACKET===\n";
            if(participants.size()==4){
                cout<<"Semifinal 1: "<<participants[0].name<<" vs "<<participants[1].name<<endl;
                cout<<"Semifinal 2: "<<participants[2].name<<" vs "<<participants[3].name<<endl;
                cout<<endl;
                cout<<"===SEMIFINAL 1===\n";
                Duel sf1(participants[0],participants[1]);
                cout<<endl<<endl<<endl;
                cout<<"===SEMIFINAL 2===\n";
                Duel sf2(participants[2],participants[3]);
                cout<<endl<<endl<<endl;
                cout<<"=== CHAMPIONSHIP FINAL ===\n";
                Duel final(participants[sf1.winner_index],participants[sf2.winner_index]);
                Tsh=sf1.sh+sf2.sh+final.sh;
                Tch=sf1.ch+sf2.ch+final.ch;
                cout<<endl;
                cout<<participants[final.winner_index].name<<" wins the "<<tournameName<<"!\n\n";
                cout<<"=== TOURNAMENT STATISTICS ===\n";
                cout<<"Champion: "<<participants[final.winner_index].name<<endl;
                cout<<"Total Battles: 3\n";
                cout<<"Total Turns: "<<sf1.turn+sf2.turn+final.turn<<endl;
                cout<<"Critical Hits: "<<Tch<<endl;
                cout<<"Super Effective Hits: "<<Tsh<<endl;
            }
        }
};

int main(){
    srand(time(0));
    Bender sable("Sable", "Air", 95, 60, 58, 85, {{{"Arctic Gust", 0, "frozen"}, {"Wind Blade", 52}, {"Tailwind", 0}, {"Cyclone Fang", 58}}});
    Bender boran("Boran", "Earth", 110, 68, 62, 50, {{{"Rockslide", 55}, {"Quicksand Trap", 0, "buried"}, {"Stone Wall", 0}, {"Seismic Slam", 70}}});

    AI_Duel svb(sable,boran);


    Bender ignis("Ignis", "Fire", 120, 82, 70, 95, {{{"Inferno Slash", 60}, {"Flame Dash", 38}, {"Ember Guard", 0}, {"Volcanic Burst", 80}}});
    Bender kestra("Kestra", "Water", 128, 78, 85, 68, {{{"Tidal Crush", 65}, {"Ice Shard", 45}, {"Mist Shield", 0}, {"Maelstrom", 85}}});
    Bender terrak("Terrak", "Earth", 135, 88, 90, 45, {{{"Stone Avalanche", 70}, {"Quake Punch", 48}, {"Bulwark", 0}, {"Mountain's Wrath", 88}}});
    Bender squall("Squall", "Air", 105, 65, 55, 100, {{{"Thunder Gale", 58}, {"Razor Wind", 35}, {"Updraft", 0, "frozen"}, {"Tempest Strike", 72}}});
    vector<Bender> participants={ignis,kestra,terrak,squall};
    Tournament championship(participants,"ELEMENTAL ARENA CHAMPIONSHIP");

    return 0;
}