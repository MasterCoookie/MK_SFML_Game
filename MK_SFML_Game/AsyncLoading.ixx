#include <thread>
#include <future>
#include "LoadingScreen.h"
export module AsyncLoading;

std::counting_semaphore<2> toLoad{ 0 };
export void LoadPlayer(std::promise<std::shared_ptr<Player>> & prom, std::string charName);
export void DisplayLoadingStatus(LoadingScreen* load);
void LoadPlayer(std::promise<std::shared_ptr<Player>>& prom, std::string charName)
{
	std::shared_ptr<Player> newPlayer = std::make_shared<Player>(charName);
	prom.set_value(newPlayer);
	toLoad.release();
	return;
}

void DisplayLoadingStatus(LoadingScreen* load)
{
	bool arebothLoaded = false;
	int loadingPercent = 0;
	while (!arebothLoaded) {
		if (toLoad.try_acquire()) {
			loadingPercent += 50;
			if (loadingPercent == 100) {
				arebothLoaded = true;
			}
		}
		load->update(loadingPercent);
		load->render();
	}

}
