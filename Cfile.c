#include "Cfile.h"
int cnt__ = 0;


int test_function(int CNT, int CNTi, int cycle, int delay)
{
    TransistorChannelsStruct tmp;

    tmp.TimeCycleIrpFrame = cycle;
    tmp.CountFrame[TRANSISTOR_CHANNEL_01] = CNTi;
    tmp.TimeDelay[TRANSISTOR_CHANNEL_01] = delay;
    cnt__ = CNT;

    return delayOnChannel(&tmp, TRANSISTOR_CHANNEL_01);
}


uint16_t getCountIrpRxFrame(void)
{
    return (uint16_t)cnt__;
}


uint32_t delayOnChannel(TransistorChannelsStruct* pTransistors, uint32_t channel)
{
  const uint32_t delayAlgo = 300U;//0.15ms
  const uint16_t minTimeCycleIrpFrame = 1980U; //izm 990  0.99ms
  const uint16_t maxTimeCycleIrpFrame = 5100U; //izm 2550 2.55ms
  uint16_t currentCountFrame = 0U;
  uint32_t maxCount = 0U;
  int tmpCount = 0U;
  uint32_t delay = 0U;
  int calc1 = 0U, calc2 = 0U;

  currentCountFrame = getCountIrpRxFrame();
	
  if (pTransistors->TimeCycleIrpFrame >= minTimeCycleIrpFrame && pTransistors->TimeCycleIrpFrame <= maxTimeCycleIrpFrame) {
	maxCount = 2000000U/pTransistors->TimeCycleIrpFrame;
	if (!(2000000U % pTransistors->TimeCycleIrpFrame)) {
	  maxCount -= 1U;
	}
  }
  else {
	maxCount = 0U;
  }
  
  if (maxCount >= pTransistors->CountFrame[channel]) {
	if (currentCountFrame < pTransistors->CountFrame[channel]) {
	  calc1 = (int)currentCountFrame - (int)pTransistors->CountFrame[channel];
	  calc2 = currentCountFrame + maxCount - pTransistors->CountFrame[channel] + 1U;
	  if ((calc1) > calc2) {
		tmpCount = calc2;
	  }
	  else {
		tmpCount = calc1;
	  }
	}
	else {
	  tmpCount = currentCountFrame - pTransistors->CountFrame[channel];
	}
  }
  else {
	tmpCount = 0U;
  }

  if ((int)pTransistors->TimeDelay[channel] - tmpCount*(int)pTransistors->TimeCycleIrpFrame < (int)delayAlgo) {
	return 0U;
  }
  else {
	delay = pTransistors->TimerDelay + pTransistors->TimeDelay[channel] - tmpCount*pTransistors->TimeCycleIrpFrame;
	if (delay > 0xFFFF) {
	  delay -= 0x00010000;
	  if (delay > pTransistors->TimerDelay) {
		return 0U;
	  }
	}
  }
  return delay;
}