#ifndef ANALYZEPROGRESSSTATITICS_H
#define ANALYZEPROGRESSSTATITICS_H

struct TimeInfo{

    int totalProcess;
    int finishedProcessCounter;
    int totalElapsedTime; // ms
    int remainingTime;    // ms


    void reset()
    {
        totalProcess = 0;
        finishedProcessCounter = 0;
        totalElapsedTime = 0;
        remainingTime = 0;
    }

    void calculateRemainingTime()
    {
        remainingTime = totalProcess * totalElapsedTime / finishedProcessCounter;
        remainingTime = remainingTime - totalElapsedTime;
    }

    int percentageOfProcess()
    {
        if(remainingTime == 0)
            return 100;

        return (totalProcess * totalElapsedTime / finishedProcessCounter) / remainingTime;
    }

};

#endif // ANALYZEPROGRESSSTATITICS_H
