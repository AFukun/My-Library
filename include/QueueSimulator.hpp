#include <queue>
#include <iostream>

class QueueSimulator {
public:
	QueueSimulator(int numberOfSimulation, double hourPerSimulation, double texiPerHour);
	void simulateAndLog(std::ostream &outputStream);

private:
	struct TexiEntity {
		int arriveTime;
		int boardTime;
		TexiEntity(int arriveTime, int boardTime) : arriveTime(arriveTime), boardTime(boardTime) {};
	};

	const int SECOND_PER_HOUR = 3600;
	const int SECOND_PER_MINUTE = 60;
	const size_t QUEUE_MAX_LEN = 60;

	std::queue<TexiEntity> texiQueue;
	int numberOfSimulation;
	double hourPerSimulation;
	double texiPerHour;

	bool queueIsFull() {
		return texiQueue.size() >= QUEUE_MAX_LEN;
	}
	int getBoardTime() {
		return rand() % 120 + 60;
	}
	bool comingNewTexi() {
		return (double)rand() / RAND_MAX < texiPerHour / SECOND_PER_HOUR;
	}
};