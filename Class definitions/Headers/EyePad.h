#pragma once
#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "Math.h"

//Camera constants used for distance calculation
#define Y_IMAGE_RES 240		//X Image resolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 49		//Axis M1013
#define PI 3.141592653

//Score limits used for target identification
#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

//Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

//Minimum area of particles to be considered
#define AREA_MINIMUM 150

//Maximum number of particles to process
#define MAX_PARTICLES 8
	
//Structure to represent the scores for the various tests used for target identification
struct Scores {
	double rectangularity;
	double aspectRatioVertical;
	double aspectRatioHorizontal;
};

struct TargetReport {
	int verticalIndex;
	int horizontalIndex;
	bool Hot;
	double totalScore;
	double leftScore;
	double rightScore;
	double tapeWidthScore;
	double verticalScore;
};

class EyePad {
private:
	double distance;
	int vTargX;
public:
	EyePad(void);
	
	void picFunctions();
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical);
	bool scoreCompare(Scores scores, bool vertical);
	double scoreRectangularity(ParticleAnalysisReport *report);
	double ratioToScore(double ratio);
	bool hotOrNot(TargetReport target);
	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report);
	DriverStationLCD *m_LCD;
	double getAlignment();
	
	
	Scores *scores;
	TargetReport target;
	const double & rDistance;
};
