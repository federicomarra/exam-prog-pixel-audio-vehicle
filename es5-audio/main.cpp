//
// Created by Federico Marra on 02/07/2020.
//
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include <utility>


class AudioTrack {
public:
    AudioTrack(std::string t, std::string a, int d) : title(t), album(a), duration(d) {}

    ~AudioTrack() {}

    void play() {
        std::cout << title << " is playing" << std::endl;
    }

    bool operator==(const AudioTrack &that) const {
        if (title == that.title && album == that.album && duration == that.duration)
            return true;
        return false;
    }

    const std::string &getTitle() const {
        return title;
    }

    void setTitle(const std::string &t) {
        title = t;
    }

    const std::string &getAlbum() const {
        return album;
    }

    void setAlbum(const std::string &a) {
        album = a;
    }

    int getDuration() const {
        return duration;
    }

    void setDuration(int d) {
        duration = d;
    }

private:
    std::string title, album;
    int duration;
};


class Playlist {
public:
    explicit Playlist(AudioTrack *t, std::string n = "Playlist", bool l = false) {
        playlist.push_back(t);
        name = n;
        loop = l;
    }

    ~Playlist() {
        playlist.clear();
    }

    void addTrack(AudioTrack *m) {
        playlist.push_back(m);
    }

    void removeTrack(std::string n) {
        auto iter = playlist.begin();
        while (iter != playlist.end()) {
            if ((*iter)->getTitle() == name) {
                iter = playlist.erase(iter);
            }
            ++iter;
        }
    }

    void playTrack(AudioTrack *m) {
        m->play();
    }

    void play() {
        int time = 0;
        do {
            for (auto m : playlist) {
                m->play();
                if (loop)
                    time += m->getDuration();
            }
        } while (time != 0 && time < 1200);  //1200sec = 20*60sec = 20min
    };

    bool operator==(const Playlist &that) const {
        if (playlist == that.playlist)
            return true;
        return false;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &n) {
        name = n;
    }

    bool isLoop() const {
        return loop;
    }

    void setLoop(bool l) {
        loop = l;
    }

private:
    std::list<AudioTrack *> playlist;
    std::string name;
    bool loop;
};

class MusicLibrary {
public:
    explicit MusicLibrary(Playlist *p) {
        library.push_back(p);
    }

    ~MusicLibrary() {
        library.clear();
    }

    void addPlaylist(Playlist *p) {
        library.push_back(p);
    }

    void play(Playlist *p) {
        p->play();
    }

    Playlist *search(const std::string &name) {
        for (auto p : library) {
            if (p->getName() == name) {
                return p;
            }
        }
        return nullptr;
    }

    bool operator==(const MusicLibrary &that) const {
        if (library == that.library)
            return true;
        return false;
    }


private:
    std::list<Playlist *> library;
};


int main() {
    std::cout << "Esercizio 5:" << std::endl << std::endl;

    auto track1 = new AudioTrack("Here Comes The Sun - The Beatles", "here_comes_the_sun.jpg", 186);
    auto track2 = new AudioTrack("Yellow Submarine - The Beatles", "yellow_submarine.jpg", 159);
    auto track3 = new AudioTrack("Stayin' Alive - Bee Gees", "stayin_alive.jpg", 285);
    auto track4 = new AudioTrack("Rocket Man - Elton John", "rocket_man.jpg", 282);
    auto track5 = new AudioTrack("Radio Ga Ga - Queen", "radio_ga_ga.jpg", 348);
    auto track6 = new AudioTrack("Bohemian Rapsody - Queen", "bohemian_rapsody.jpg", 354);

    auto sixty = new Playlist(track1, "Anni '60", false);
    auto seventy = new Playlist(track3, "Anni '70", false);
    auto eighty = new Playlist(track5, "Anni '80", true);

    auto library = new MusicLibrary(eighty);

    sixty->addTrack(track2);
    sixty->play();
    sixty->removeTrack("Yellow Submarine - The Beatles");

    seventy->addTrack(track4);
    seventy->playTrack(track3);

    eighty->addTrack(track6);
    eighty->play();     //loop=true

    library->addPlaylist(seventy);
    library->addPlaylist(sixty);
    int pl;
    std::cout << "Immettere nome playlist: Anni '60 = 60, Anni '70 = 70, Anni '80 = 80 : ";
    std::cin >> pl;
    if (pl == 60) {
        library->play(library->search("Anni '60"));
    } else if (pl == 70) {
        library->play(library->search("Anni '70"));
    } else if (pl == 80) {
        library->play(library->search("Anni '80"));
    }


    delete library;     //libero tutta la memoria occupata, evito il memory leak
    delete sixty;
    delete seventy;
    delete eighty;
    delete track1;
    delete track2;
    delete track3;
    delete track4;
    delete track5;
    delete track6;
}
