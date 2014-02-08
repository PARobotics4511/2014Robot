#include "Headers/EyePad.h"
#include <cmath>

int verticalTargets[MAX_PARTICLES];
int horizontalTargets[MAX_PARTICLES];
int verticalTargetCount, horizontalTargetCount;
Threshold threshold(115, 145, 0x0, 255, 205, 255);	//HSV threshold criteria, ranges are in that order ie. Hue is 60-100
ParticleFilterCriteria2 criteria[] = {
	{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
};

AxisCamera &camera = AxisCamera::GetInstance("10.45.11.11");
//Initialize camera!!!!
//EyePad::EyePad() : camera("10.45.11.11") {}
EyePad::EyePad() : rDistance(distance) {
	m_LCD = DriverStationLCD::GetInstance();
}

//Functions for taking and analyzing the picture
void EyePad::picFunctions() {
	//takes the picture
	ColorImage *image;
    image = camera.GetImage();
	BinaryImage *thresholdImage = image->ThresholdHSV(threshold);	// get just the target pixels; white in our case
	thresholdImage->Write("/threshold.bmp");
	BinaryImage *filteredImage = thresholdImage->ParticleFilter(criteria, 1);	//Remove small particles
	filteredImage->Write("Filtered.bmp");
	
	//analyzes the particles and turns them into scores
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();  //get a particle analysis report for each particle
	verticalTargetCount = horizontalTargetCount = 0;
	scores = new Scores[reports->size()];
	
	double height;
	
	if(scores > 0) {
		for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++) {
			ParticleAnalysisReport *report = &(reports->at(i));
						
			//Score each particle on rectangularity and aspect ratio
			scores[i].rectangularity = scoreRectangularity(report);
			scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage, report, true);
			scores[i].aspectRatioHorizontal = scoreAspectRatio(filteredImage, report, false);			
						
			//Check if the particle is a horizontal target, if not, check if it's a vertical target
			if(scoreCompare(scores[i], false)) {
				//m_LCD->Printf(DriverStationLCD::Line(0),1,"ptcle %d is a H-Targ centX: %d centY: %d", i, report->center_mass_x, report->center_mass_y);
				horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
			}
			else if (scoreCompare(scores[i], true)) {
				//m_LCD->Printf(DriverStationLCD::Line(0),1,"ptcle %d is a V-Targ centX: %d centY: %d", i, report->center_mass_x, report->center_mass_y);
				verticalTargets[verticalTargetCount++] = i;  //Add particle to target array and increment count
			}
			else {
				//m_LCD->Printf(DriverStationLCD::Line(0),1,"particle: %d  is not a Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
			}
			//m_LCD->Printf(DriverStationLCD::Line(1),1,"Scores rect: %f  ARvert: %f", scores[i].rectangularity, scores[i].aspectRatioVertical);
			//m_LCD->Printf(DriverStationLCD::Line(2),1,"ARhoriz: %f", scores[i].aspectRatioHorizontal);	
		}
	

		//Zero out scores and set verticalIndex to first target in case there are no horizontal targets
		target.totalScore = target.leftScore = target.rightScore = target.tapeWidthScore = target.verticalScore = 0;
		target.verticalIndex = verticalTargets[0];
		for (int i = 0; i < verticalTargetCount; i++) {
			ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
			height = verticalReport->boundingRect.height;
			for (int j = 0; j < horizontalTargetCount; j++) {
				ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
				double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;
		
				//Measure equivalent rectangle sides for use in score calculation
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
							
				//Determine if the horizontal target is in the expected location to the left of the vertical target
				leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
				//Determine if the horizontal target is in the expected location to the right of the  vertical target
				rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
				//Determine if the width of the tape on the two targets appears to be the same
				tapeWidthScore = ratioToScore(vertWidth/horizHeight);
				//Determine if the vertical location of the horizontal target appears to be correct
				verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
				total = leftScore > rightScore ? leftScore:rightScore;
				total += tapeWidthScore + verticalScore;
							
				//If the target is the best detected so far store the information about it
				if(total > target.totalScore) {
					target.horizontalIndex = horizontalTargets[j];
					target.verticalIndex = verticalTargets[i];
					target.totalScore = total;
					target.leftScore = leftScore;
					target.rightScore = rightScore;
					target.tapeWidthScore = tapeWidthScore;
					target.verticalScore = verticalScore;
				}
			}
		
			//Determine if the best target is a Hot target
			target.Hot = hotOrNot(target);
		}
		
		if(verticalTargetCount > 0) {
			//Information about the target is contained in the "target" structure
			//To get measurement information such as sizes or locations use the
			//horizontal or vertical index to get the particle report as shown below
			//ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
			//double distance = computeDistance(filteredImage, distanceReport);
			//distance = 0.852/tan((0.445*height/Y_IMAGE_RES));
			if(target.Hot) {
				m_LCD->Printf(DriverStationLCD::Line(0),1,"Hot: True ");
			}
			else {
				m_LCD->Printf(DriverStationLCD::Line(0),1,"Hot: False");
			}
			m_LCD->Printf(DriverStationLCD::Line(1),1,"Distance: %f", distance);
		}
	}
}
	
double EyePad::scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical) {
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	idealAspectRatio = vertical ? (4.0/32) : (23.5/4);	//Vertical reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall
		
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
		
	//Divide width by height to measure aspect ratio
	if(report->boundingRect.width > report->boundingRect.height){
		//particle is wider than it is tall, divide long by short
		aspectRatio = ratioToScore(((rectLong/rectShort)/idealAspectRatio));
	}
	else {
		//particle is taller than it is wide, divide short by long
		aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio));
	}
	return aspectRatio;		//force to be in range 0-100
}

bool EyePad::scoreCompare(Scores scores, bool vertical) {
	bool isTarget = true;
	isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
	if(vertical){
		isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
	}
	else {
		isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
	}
	return isTarget;
}

double EyePad::scoreRectangularity(ParticleAnalysisReport *report) {
	if(report->boundingRect.width*report->boundingRect.height !=0) {
		return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
	}
	else {
		return 0;
	}	
}

double EyePad::ratioToScore(double ratio) {
	return (max(0, min(100*(1-fabs(1-ratio)), 100)));
}

bool EyePad::hotOrNot(TargetReport target) {
	bool isHot = true;
		
	isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
	isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
	isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);
		
	return isHot;
}

double EyePad::computeDistance (BinaryImage *image, ParticleAnalysisReport *report) {
	/*
	double rectLong, height;
	int targetHeight;
		
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	//using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
	//on skewed rectangles
	height = min(report->boundingRect.height, rectLong);
	targetHeight = 32;
		
	return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
	*/
	distance = 0.852/tan((0.445*report->boundingRect.height/Y_IMAGE_RES));
	return distance;
}

double EyePad::getAlignment(void) {
	return 0;
}
