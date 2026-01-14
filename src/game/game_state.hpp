#ifndef GAME_STATE_H_
#define GAME_STATE_H_

enum class State
{
    kPlaying,
    kGameOver,
    kWin
};

class GameState
{
  public:
    GameState() = default;
    ~GameState() = default;

    void update();

    inline void set_ghosts_frightened() { _frightenedTimer = _frightenedDuration; };
    inline bool are_ghosts_frightened() const { return _frightenedTimer > 0; };

    inline bool has_ended() const { return _currentState != State::kPlaying; };
    inline const State get_state() const { return _currentState; };
    inline void set_state(State state) { _currentState = state; };

    inline void add_points(int value) { _points += value; };
    inline void reset_points(int value) { _points = 0; };

  private:
    State _currentState{ State::kPlaying };
    bool _ghostsFrightened{ false };
    bool _gameOver{ false };
    int _points = 0;

    int _frightenedDuration{ 180 };
    int _frightenedTimer{};

    void update_frightened_state();
};

#endif
