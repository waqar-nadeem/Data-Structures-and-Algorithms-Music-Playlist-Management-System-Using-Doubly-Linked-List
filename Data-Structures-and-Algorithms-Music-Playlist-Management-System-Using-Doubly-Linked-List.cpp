#include <iostream>
#include <string>
using namespace std;

struct Song {
    string songTitle;
    string artist;
    int duration;  
    Song* prev;
    Song* next;

    Song(string title, string artistName, int dur) 
        : songTitle(title), artist(artistName), duration(dur), prev(nullptr), next(nullptr) {}
};

struct Playlist {
    string playlistName;
    Song* head;
    Song* tail;

    Playlist(string name) : playlistName(name), head(nullptr), tail(nullptr) {}

    void addSong(string title, string artist, int duration) {
        Song* newSong = new Song(title, artist, duration);
        if (!head) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song \"" << title << "\" added to playlist \"" << playlistName << "\".\n";
    }

    void removeSong(string title) {
        Song* temp = head;
        while (temp) {
            if (temp->songTitle == title) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                cout << "Song \"" << title << "\" removed from playlist \"" << playlistName << "\".\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song \"" << title << "\" not found in playlist \"" << playlistName << "\".\n";
    }

    void moveSong(string title, int position) {
        Song* temp = head;
        int currentPos = 0;
        while (temp) {
            if (temp->songTitle == title) {
                if (currentPos == position) {
                    cout << "Song is already in the requested position.\n";
                    return;
                }
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;

                if (position == 0) {
                    temp->prev = nullptr;
                    temp->next = head;
                    if (head) head->prev = temp;
                    head = temp;
                } else {
                    Song* temp2 = head;
                    int pos = 0;
                    while (temp2 && pos < position - 1) {
                        temp2 = temp2->next;
                        pos++;
                    }
                    if (temp2) {
                        temp->prev = temp2;
                        temp->next = temp2->next;
                        if (temp2->next) temp2->next->prev = temp;
                        temp2->next = temp;
                    }
                }
                cout << "Song \"" << title << "\" moved to position " << position << " in playlist \"" << playlistName << "\".\n";
                return;
            }
            temp = temp->next;
            currentPos++;
        }
        cout << "Song \"" << title << "\" not found in playlist \"" << playlistName << "\".\n";
    }

    void displayPlaylist() {
        if (!head) {
            cout << "Playlist \"" << playlistName << "\" is empty.\n";
            return;
        }
        cout << "Songs in playlist \"" << playlistName << "\":\n";
        Song* temp = head;
        while (temp) {
            cout << temp->songTitle << " by " << temp->artist << " (" << temp->duration << " seconds)\n";
            temp = temp->next;
        }
    }
};

class MusicPlayer {
private:
    Playlist* currentPlaylist;

public:
    MusicPlayer() : currentPlaylist(nullptr) {}

    void createPlaylist(string name) {
        currentPlaylist = new Playlist(name);
        cout << "Playlist \"" << name << "\" created.\n";
    }

    void addSongToPlaylist(string title, string artist, int duration) {
        if (currentPlaylist) {
            currentPlaylist->addSong(title, artist, duration);
        } else {
            cout << "No playlist selected. Please create a playlist first.\n";
        }
    }

    void removeSongFromPlaylist(string title) {
        if (currentPlaylist) {
            currentPlaylist->removeSong(title);
        } else {
            cout << "No playlist selected. Please create a playlist first.\n";
        }
    }

    void moveSongInPlaylist(string title, int position) {
        if (currentPlaylist) {
            currentPlaylist->moveSong(title, position);
        } else {
            cout << "No playlist selected. Please create a playlist first.\n";
        }
    }

    void displaySongsInPlaylist() {
        if (currentPlaylist) {
            currentPlaylist->displayPlaylist();
        } else {
            cout << "No playlist selected. Please create a playlist first.\n";
        }
    }
};

int main() {
    MusicPlayer player;
    int choice;

    while (true) {
        cout << "\nMusic Playlist Management Menu:\n";
        cout << "1. Create Playlist\n";
        cout << "2. Add Song to Playlist\n";
        cout << "3. Remove Song from Playlist\n";
        cout << "4. Move Song in Playlist\n";
        cout << "5. Display Songs in Playlist\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string title, artist;
        int duration, position;

        switch (choice) {
            case 1:
                cout << "Enter playlist name: ";
                cin >> title;
                player.createPlaylist(title);
                break;
            case 2:
                cout << "Enter song title: ";
                cin >> title;
                cout << "Enter artist: ";
                cin >> artist;
                cout << "Enter song duration (in seconds): ";
                cin >> duration;
                player.addSongToPlaylist(title, artist, duration);
                break;
            case 3:
                cout << "Enter song title to remove: ";
                cin >> title;
                player.removeSongFromPlaylist(title);
                break;
            case 4:
                cout << "Enter song title to move: ";
                cin >> title;
                cout << "Enter new position (starting from 0): ";
                cin >> position;
                player.moveSongInPlaylist(title, position);
                break;
            case 5:
                player.displaySongsInPlaylist();
                break;
            case 6:
                cout << "Exiting Music Playlist Management System.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
