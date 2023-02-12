
#define uint8_t             unsigned char
#define uint16_t            unsigned short
#define uint32_t            unsigned int



enum {
  TRANSISTOR_CHANNEL_01         = 0U,
  TRANSISTOR_CHANNEL_02         = 1U,
  TRANSISTOR_CHANNEL_03         = 2U,
  ALL_TRANSISTOR_CHANNELS		= 3U
};

typedef struct {
  uint32_t Command[ALL_TRANSISTOR_CHANNELS];
  uint32_t Status[ALL_TRANSISTOR_CHANNELS];
  uint32_t ExternalSwitchOff[ALL_TRANSISTOR_CHANNELS];
  uint32_t Block[ALL_TRANSISTOR_CHANNELS];
  uint16_t CurrentZero[ALL_TRANSISTOR_CHANNELS];
  uint8_t Current[ALL_TRANSISTOR_CHANNELS];
  uint32_t Error[ALL_TRANSISTOR_CHANNELS];
  uint16_t CountFrame[ALL_TRANSISTOR_CHANNELS];
  uint32_t TimeDelay[ALL_TRANSISTOR_CHANNELS];
  uint32_t TimeCycleIrpFrame;
  uint32_t TimerDelay;
  uint32_t FlagDelay[ALL_TRANSISTOR_CHANNELS];
} TransistorChannelsStruct;



uint32_t delayOnChannel(TransistorChannelsStruct* pTransistors, uint32_t channel);
int test_function(int CNT, int CNTi, int cycle, int delay);
uint16_t getCountIrpRxFrame(void);