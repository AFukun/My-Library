#include "QueueSimulator.hpp"
#include <cstdlib>

QueueSimulator::QueueSimulator(int numberOfSimulation, double hourPerSimulation, double texiPerHour)
	:numberOfSimulation(numberOfSimulation),
	hourPerSimulation(hourPerSimulation),
	texiPerHour(texiPerHour) {}

void QueueSimulator::simulateAndLog(std::ostream &out) {
	const int simulationTimeInSecond = static_cast<int>(hourPerSimulation * SECOND_PER_HOUR);
	double sumAverageWaitTime = 0.0;
	int  sumTotalTexi = 0;
	srand((unsigned)time(0));

	for (int sim = 0;sim < numberOfSimulation;sim++) {
		int totalWaitTime = 0, totalTexi = 0, servedTexi = 0, texiTurnAway = 0;
		double averageWaitTime = 0.0;

		for (int timer = 0;timer < simulationTimeInSecond;timer++) {
			if (comingNewTexi()) {
				if (!queueIsFull()) {
					texiQueue.push(TexiEntity(timer, getBoardTime()));
					totalTexi++;
				} else {
					texiTurnAway++;
				}
			}


			if (!texiQueue.empty()) {
				if (texiQueue.front().boardTime > 0) {
					texiQueue.front().boardTime--;
				} else {
					TexiEntity &front = texiQueue.front();
					int waitTime = timer - front.arriveTime;
					totalWaitTime += waitTime;
					servedTexi++;
					texiQueue.pop();
				}
			}
		}
		averageWaitTime = (double)totalWaitTime / servedTexi;
		using std::endl;
		out << "------------------------\n"
			<< "模拟次数：" << sim << endl;
		out << "总共到来的出租车：" << totalTexi << endl
			<< "接到客人的出租车：" << servedTexi << endl
			<< "掉头走掉的出租车：" << texiTurnAway << endl
			<< "平均等待时间：" << averageWaitTime << endl;
		sumAverageWaitTime += averageWaitTime;
		sumTotalTexi += totalTexi;
		while (!texiQueue.empty()) texiQueue.pop();
	}
	using std::endl;
	out << "------------------------" << endl;
	out << numberOfSimulation << "次模拟中出租车平均等待时间"
		<< sumAverageWaitTime / numberOfSimulation / SECOND_PER_MINUTE
		<< "分钟，" << hourPerSimulation << "小时内进行排队的出租车有"
		<< (double)sumTotalTexi / numberOfSimulation << "辆。\n";
}
