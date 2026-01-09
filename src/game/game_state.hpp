#ifndef GAME_STATE_H_
#define GAME_STATE_H_

class GameState
{
  public:
    GameState() = default;
    ~GameState() = default;

    void update();

    inline void set_ghosts_frightened() { _frightenedTimer = _frightenedDuration; };
    inline bool are_ghosts_frightened() const { return _frightenedTimer > 0; };

    inline void set_game_over(bool value) { _gameOver = value; };

    inline void add_points(int value) { _points += value; };
    inline void reset_points(int value) { _points = 0; };

  private:
    bool _ghostsFrightened{ false };
    bool _gameOver{ false };
    int _points = 0;

    int _frightenedDuration{ 180 };
    int _frightenedTimer{};

    void update_frightened_state();
};

#endif
