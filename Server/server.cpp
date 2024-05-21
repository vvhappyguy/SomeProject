#include <array>
#include <chrono>
#include <crtdbg.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class User {};

class Lobby {
public:
  string name;
  vector<User> users;
  bool deletable = true;
  chrono::time_point<chrono::system_clock> lastUpdate =
      chrono::system_clock::now();
};

class Game {
public:
  static constexpr size_t lobbiesMaxNumber = 10;
  using LobbyList = vector<Lobby>;
  LobbyList lobbies;

  void createLobby(string name, bool deleteable = true) {
    if (lobbies.size() >= lobbiesMaxNumber) {
      cout << "Too many lobbies!" << endl;
      return;
    }
    Lobby lobby;
    lobby.name = name;
    lobby.deletable = deleteable;
    lobbies.push_back(lobby); // copy
    cout << "Lobby added" << endl;
  };

  unique_ptr<LobbyList> getLobbyList() {
    auto ptr = unique_ptr<LobbyList>(&lobbies);
    return ptr;
  }
};

void printLobbyList(Game::LobbyList *list) {
  cout << "printLobbyList " << list->size() << endl;
  for (auto lobby : *list) {
    cout << lobby.name << endl;
  }
}

void lobbiesWatchdog() {}

enum class PlayerState { login, menu, lobby, game };

int main(int argc, char *argv[]) {
  Game game;
  auto lobbyList = game.getLobbyList();
  printLobbyList(lobbyList.get());

  game.createLobby("123123123", false);

  for (int i = 0; i < Game::lobbiesMaxNumber + 1; ++i) {
    game.createLobby(to_string(i));
  }

  // lobbyList = game.getLobbyList();
  printLobbyList(lobbyList.get());

  string input;
  cin >> input;
  while (input != "exit") {
    if (input == "create") {
      game.createLobby("1");
    } else if (input == "update") {
      // game.updateLobby("1");
    } else {
      cout << "unkown" << endl;
    }
  }

  return 0;
}