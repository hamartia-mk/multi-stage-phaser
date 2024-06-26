#pragma once
#include <pluginterfaces/vst/vsttypes.h>

/*
* This is an implementation of a 2nd order APF
*/
class AllPassFilter
{
public:
	AllPassFilter();
	~AllPassFilter();

	Steinberg::Vst::Sample32 processSample(Steinberg::Vst::Sample32 input, Steinberg::int32 channelNumber);
	void setNewOscillatorValue(float newValue) { oscillatorValue = newValue; };
	void setSampleRate(Steinberg::Vst::SampleRate newRate) { sampleRate = newRate; };

	void setCornerFrequency(float normalisedValue)
	{
		double diff = maxFrequency - minFrequency;
		double newValue = minFrequency + (diff * normalisedValue);
		if (newValue > maxFrequency)
		{
			newValue = maxFrequency;
		}
		cornerFrequency = newValue;
	};

	void setEnable(float newValue)
	{
		if (newValue == 0.0f)
			enabled = false;
		else
			enabled = true;
	};

	bool isEnabled() { return enabled; };

private:
	const double minFrequency = 40;
	const double maxFrequency = 10000;
	const float steepness = 1.1f; // Q

	Steinberg::Vst::SampleRate sampleRate = 44100;
	float oscillatorValue = 0.0f;
	double cornerFrequency = 500; //also known as centre frequency
	float coef = 0.f;
	bool enabled = true;


	//buffers to store previous input samples and their outputs
	Steinberg::Vst::Sample32 bufferedX1[2] = { Steinberg::Vst::Sample32(), Steinberg::Vst::Sample32() }; //a processed value from the previous sample's processing.
	Steinberg::Vst::Sample32 bufferedX2[2] = { Steinberg::Vst::Sample32(), Steinberg::Vst::Sample32() };
	Steinberg::Vst::Sample32 bufferedY1[2] = { Steinberg::Vst::Sample32(), Steinberg::Vst::Sample32() };
	Steinberg::Vst::Sample32 bufferedY2[2] = { Steinberg::Vst::Sample32(), Steinberg::Vst::Sample32() };

	double getModulatedCornerFreq();
	float calculateCoefficient();
};