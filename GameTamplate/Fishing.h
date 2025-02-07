#include "GameState.h"
#include "ProgressBar.h"
#include "Ring.h"
class Fishing :
    public GameState
{
private:
    ProgressBar* _progressBar;
    float _maxFishingTime;
    float _remainingFishingTime;
    Ring* _ring;
public:
    Fishing(Player* player, Fish* fish) : GameState(player, fish){}
    void onStateEnter();
    void onStateUpdate(float deltaTime);
    void onStateExit();
    void render();
    float getRemainigFishingTime();
};