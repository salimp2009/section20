#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <fstream>


class Song {
  friend std::ostream& operator<<(std::ostream& os, const Song& song); 
  std::string name;
  std::string artist;
  int rating;
public:
  Song()=default;
  Song(std::string name, std::string artist, int rating)
    : name{std::move(name)}, artist{std::move(artist)}, rating{std::move(rating)} 
    { }
   const std::string&   get_name() const& {return name;}
   const std::string&   get_artist() const& {return artist;}
   int get_rating() const {return rating;}
   
   bool operator<(const Song& rhs) const {
       return this->name<rhs.name;
   }
   
   bool operator==(const Song& rhs) const {
       return this->name==rhs.name;
   }
};

std::ostream& operator<<(std::ostream& os, const Song& song) {
        os<<std::setw(20)<<std::left<<song.name
          <<std::setw(30)<<std::left<<song.artist
          <<std::setw(2)<<std::right<<song.rating;
        return os;
    }
    
void display_menu() {
    std::cout<<"\nF - Play First Song\n";
    std::cout<<"B - Play Last Song\n";
    std::cout<<"N - Play Next Song\n";
    std::cout<<"P - Play Previous Song\n";
    std::cout<<"A - Add and Play a New Song\n";
    std::cout<<"L - List the Current Playlist\n";
    std::cout<<"S - Save the  Playlist\n";
    std::cout<<"U - Upload the last saved Playlist\n";
    std::cout<<"=========================================\n";
    std::cout<<"Enter a selection(Q to quit): "; 
}

void play_current_song(const Song& song) {
    // function display;
    // Playing; 'playing song'
    std::cout<<"\nPlaying: "<<song;
} 

void display_playlist(const std::list<Song>& playlist, const Song& current_song) {
    // function to display current playlist
    // and the current song playing;
    std::cout<<"\nCurrent Playlist: \n";
    for(const auto& song:playlist)
        std::cout<<song<<'\n';
    play_current_song(current_song);
}

void add_song(std::list<Song>& playlist, std::list<Song>::iterator& current_song) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"\nAdding and playing new song\n";
            std::cout<<"\nEnter the name of the song: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout<<"\nEnter the song artist: ";
            std::string artist;
            std::getline(std::cin, artist);
            std::cout<<"\nEnter the rating (1-5): ";
            int rating;
            std::cin>>rating;
            current_song=playlist.emplace(current_song, name, artist, rating);         
}

void save_playlist(std::list<Song>& playlist, std::list<Song>::iterator& current_song) {
        std::ofstream ofs("../Playlist.txt");
        if(!ofs) {
        std::cerr<<"\nError openning output file...\n";
    }
        for(const auto& s:playlist)
            ofs<<s<<'\n';
        ofs<<*current_song;
        ofs.close();        
}

//void upload_playlist() {
//    std::ifstream ifs("Playlist.txt")
//    std::ofstream ifs("../Playlist.txt");
//        if(!ofs) {
//        std::cerr<<"\nError openning output file...\n";
//    }
//        // to be implemented
//}


int main() {
    std::list<Song>playlist {
        {"God's Plan",          "Drake",                     5}, 
        {"Never Be The Same",   "Camila Cabello",            5},
        {"Pray For Me",         "The Weekend and K.Lamar",   4},
        {"The Middle",          "Zedd, Maren Morris & Grey", 5},
        {"Wait",                "Maroon 5",                  4},
        {"Whatever It Takes",   "Imagine Dragons",           3} 
    };
        
    std::list<Song>::iterator current_song=playlist.begin();
    display_playlist(playlist, *current_song);
    
    
    char selection{};                       
    do {
        display_menu();
        std::cin>>selection;
        selection=std::toupper(selection);
        switch(selection) {
            case 'F': 
            {   
                std::cout<<"\nPlaying First Song\n";
                current_song=playlist.begin();
                play_current_song(*current_song);
                break;
            }
            case 'B': 
            {   
                std::cout<<"\nPlaying Last Song\n";
                current_song=playlist.end();
                --current_song;
                play_current_song(*current_song);
                break;
            }
            case 'N':
            {   
                std::cout<<"\nPlaying Next Song\n";
                ++current_song;
                if(current_song==playlist.end()) {
                    std::cout<<"\nWrapping to start of playlist\n";
                    current_song=playlist.begin();
                }
                
                play_current_song(*current_song);
                break;
            }
            case 'P': 
            {   
                std::cout<<"\nPlaying Previous Song\n";
                if(current_song==playlist.begin()) {
                    current_song=playlist.end();
                } 
                --current_song;
                play_current_song(*current_song);
                break;
            }
            case 'A':
            {
                add_song(playlist, current_song);
                play_current_song(*current_song);
                break;
            }
            
            case 'L':
            {
                std::cout<<'\n';
                display_playlist(playlist, *current_song);
                break;
            }
             case 'S':  
            {
                save_playlist(playlist, current_song);
                std::cout<<"\nPlay list and current song saved...!!\n";
                break;
            }
            
            default:
            {
                if(!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else if(selection=='Q') {
                    std::cout<<"\nQuitting...!\n";
                }
                else {
                    std::cout<<"\nIllegal selection, try again please...!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }  
        } // exit from switch
        
    } while(selection!='Q');
 
    std::cout<<"\nThanks for listening...\n";
    std::cout<<'\n';
    
 return 0;
}