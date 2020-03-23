#include "Track.h"

Track::Track() {}
Track::Track(int trackType) {
	this->initializeTrackPoints(trackType);
}
Track::~Track() {}
void Track::addPointToList(float x, float y, float z, int action) {
	this->listOfPoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, action));
}
void Track::addInteractableStripToList() {
	this->listOfLaneStrips.push_back(std::make_unique<TrackInteractableStrip>());
}

void Track::initializeTrackPoints(int trackType) {
	if (trackType == trackTypeConstants::OVAL_TEST) {
		this->addPointToList(69.10, -2.65, -71.48, trackDrivingPointActions::START);
		this->addPointToList(-3.70, -2.26, -72.82, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(-42.75, -3.45, -70.97, trackDrivingPointActions::TURN_IN);
		this->addPointToList(-69.11, -2.60, -43.99, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-87.52, -2.61, -25.72, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-59.48, -2.58, 16.92, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-19.16, -2.58, 43.87, trackDrivingPointActions::TURN_EXIT);
		this->addPointToList(58.33, -2.60, 42.76, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(122.95, -2.62, 32.60, trackDrivingPointActions::TURN_IN);
		this->addPointToList(150.05, -2.63, 5.78, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(129.00, -2.58, -57.16, trackDrivingPointActions::TURN_EXIT);
		/*
		this->addPointToList(69.10, -2.65, -71.48, trackDrivingPointActions::START);
		this->addPointToList(12.70, -2.48, -70.30, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(-56.95, -2.70, -68.95, trackDrivingPointActions::TURN_IN);
		this->addPointToList(-77.63, -2.60, -36.85, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-69.18, -2.59, 7.72, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-53.39, -2.59, 31.98, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(10.72, -2.64, 57.39, trackDrivingPointActions::TURN_EXIT);
		this->addPointToList(58.33, -2.60, 54.76, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(115.87, -2.68, 41.60, trackDrivingPointActions::TURN_IN);
		this->addPointToList(150.66, -2.68, 18.69, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(152.05, -2.68, -34.12, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(102.00, -2.66, -70.70, trackDrivingPointActions::TURN_EXIT);
		*/
	}
	else if (trackType == trackTypeConstants::OVAL) {
		this->addPointToList(69.10, -2.65, -71.48, trackDrivingPointActions::START);
		this->addPointToList(20.70, -2.48, -70.30, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(-42.95, -2.70, -80.95, trackDrivingPointActions::TURN_IN);
		this->addPointToList(-77.63, -2.60, -36.85, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-69.18, -2.59, 7.72, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-53.39, -2.59, 31.98, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(1.72, -2.64, 60.39, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(52.33, -2.60, 64.76, trackDrivingPointActions::TURN_EXIT);
		this->addPointToList(78.33, -2.60, 60.76, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(115.87, -2.68, 41.60, trackDrivingPointActions::TURN_IN);
		this->addPointToList(150.66, -2.68, 18.69, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(159.05, -2.68, -22.62, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(130.66, -2.68, -58.69, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(100.00, -2.66, -68.70, trackDrivingPointActions::TURN_EXIT);
    
    //InteractZonePoints
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();

		TrackInteractableStrip z1 = *this->listOfLaneStrips.at(0);
		z1.addLanePoint(-60.24, -2.56, -7.90, trackInteractableObjects::EMPTY);
		z1.addLanePoint(-68.14, -2.58, -4.85, trackInteractableObjects::EMPTY);
		z1.addLanePoint(-72.65, -2.59, -3.10, trackInteractableObjects::EMPTY);
		z1.addLanePoint(-78.62, -2.60, -0.79, trackInteractableObjects::EMPTY);
		z1.addLanePoint(-84.51, -2.62, 1.49, trackInteractableObjects::EMPTY);
		z1.addLanePoint(-92.22, -2.64, 4.48, trackInteractableObjects::EMPTY);

		TrackInteractableStrip z2 = *this->listOfLaneStrips.at(1);
		z2.addLanePoint(10.36, -2.51, 34.32, trackInteractableObjects::EMPTY);
		z2.addLanePoint(9.95, -2.55, 40.86, trackInteractableObjects::EMPTY);
		z2.addLanePoint(9.41, -2.60, 49.43, trackInteractableObjects::EMPTY);
		z2.addLanePoint(8.89, -2.64, 57.65, trackInteractableObjects::EMPTY);
		z2.addLanePoint(8.43, -2.68, 64.97, trackInteractableObjects::EMPTY);

		TrackInteractableStrip z3 = *this->listOfLaneStrips.at(2);
		z3.addLanePoint(31.58, -2.50, 32.87, trackInteractableObjects::EMPTY);
		z3.addLanePoint(32.04, -2.52, 37.85, trackInteractableObjects::EMPTY);
		z3.addLanePoint(32.81, -2.56, 43.47, trackInteractableObjects::EMPTY);
		z3.addLanePoint(33.36, -2.59, 48.19, trackInteractableObjects::EMPTY);
		z3.addLanePoint(34.19, -2.64, 55.29, trackInteractableObjects::EMPTY);
		z3.addLanePoint(35.12, -2.68, 63.29, trackInteractableObjects::EMPTY);

		TrackInteractableStrip z4 = *this->listOfLaneStrips.at(3);
		z4.addLanePoint(66.87, -2.48, 26.56, trackInteractableObjects::EMPTY);
		z4.addLanePoint(68.08, -2.53, 33.87, trackInteractableObjects::EMPTY);
		z4.addLanePoint(69.19, -2.58, 40.59, trackInteractableObjects::EMPTY);
		z4.addLanePoint(70.35, -2.62, 47.57, trackInteractableObjects::EMPTY);
		z4.addLanePoint(71.77, -2.68, 56.15, trackInteractableObjects::EMPTY);
		z4.addLanePoint(72.96, -2.75, 65.72, trackInteractableObjects::EMPTY);

		TrackInteractableStrip z5 = *this->listOfLaneStrips.at(4);
		z5.addLanePoint(66.87, -2.48, 26.56, trackInteractableObjects::EMPTY);
		z5.addLanePoint(68.08, -2.53, 33.87, trackInteractableObjects::EMPTY);
		z5.addLanePoint(69.19, -2.58, 40.59, trackInteractableObjects::EMPTY);
		z5.addLanePoint(70.35, -2.62, 47.57, trackInteractableObjects::EMPTY);
		z5.addLanePoint(71.77, -2.68, 56.15, trackInteractableObjects::EMPTY);
		z5.addLanePoint(72.96, -2.75, 65.72, trackInteractableObjects::EMPTY);
	}
	else if (trackType == trackTypeConstants::TESLA_T) {

	}
}

//To use if you get stuck
void Track::performStuckCorrectionMove(Vehicle* v) {
	TrackDrivingPoint* currentTarget = &v->curTarget;
	float angleToTurn = getAngleToTurnBy(currentTarget, v);

	if (angleToTurn < 0) {
		v->forwards(0.f);
		v->turn(0.4f); //going in reverse
		v->reverse(0.9f);
	}
	else {
		v->forwards(0.f);
		v->turn(-0.4f);
		v->reverse(0.9f);
	}
	
}

void Track::performMove(Vehicle* v) {
	TrackDrivingPoint* pastTarget = &v->pastTarget;
	TrackDrivingPoint* currentTarget = &v->curTarget;

	int pastAction = pastTarget->actionToTake;
	int currentAction = currentTarget->actionToTake;

	PxU32 curGear = v->gVehicle4W->mDriveDynData.getCurrentGear();
	float angleToTurn = getAngleToTurnBy(currentTarget, v);

	//The method names themselves tell you for what combinations the method is for
	if (pastAction == trackDrivingPointActions::START && currentAction == trackDrivingPointActions::SLOW_DOWN) {
		//The code for the initial 
		this->pastStartCurrentSlowdown(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::TURN_EXIT && currentAction == trackDrivingPointActions::SLOW_DOWN) {
		this->pastTurnExitCurrentSlowDown(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::TURN_EXIT && currentAction == trackDrivingPointActions::START) {
		this->pastTurnExitCurrentStart(curGear, angleToTurn, v);
	}

	//******************************************************************************************************************
	//**************************************** TURNING STUFF ***********************************************************
	//******************************************************************************************************************
	else if (pastAction == trackDrivingPointActions::SLOW_DOWN && currentAction == trackDrivingPointActions::TURN_IN) {
		//Slow down before entering the turn
		this->pastSlowDownCurrentTurnIn(curGear, angleToTurn, v);
	}

	//This is for normal turns or short U turn style
	else if (pastAction == trackDrivingPointActions::TURN_IN && currentAction == trackDrivingPointActions::APEX_MAJOR) {
		//Hit the apex (midpoint, kinda) of the turn
		this->pastTurnInCurrentMajor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MAJOR && currentAction == trackDrivingPointActions::TURN_EXIT) {
		//Reach the exit point of the turn
		this->pastMajorCurrentExit(curGear, angleToTurn, v);
	}

	//This is for long U turn style turns (two minors one major)
	else if (pastAction == trackDrivingPointActions::TURN_IN && currentAction == trackDrivingPointActions::APEX_MINOR) {
		//First apex of the turn
		this->pastTurnInCurrentMinor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MINOR && currentAction == trackDrivingPointActions::APEX_MAJOR) {
		//Imaginary Apex of turn (help co-ordinate Ai position in case of spinouts)
		this->pastMinorCurrentMajor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MAJOR && currentAction == trackDrivingPointActions::APEX_MINOR) {
		//second (third) apex of the turn
		this->pastMajorCurrentMinor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MINOR && currentAction == trackDrivingPointActions::TURN_EXIT) {
		//Reach exit point of turn
		this->pastMinorCurrentExit(curGear, angleToTurn, v);
	}

	else {
		v->forwards(0.f);
		v->reverse(1.f);
		v->turn(0.f);
	}

	
}

/*
I AM WELL AWARE THESE METHODS CONTAIN DUPLICATED CODE, HOWEVER IT IS TO ALLOW FOR EASY FINE TUNING OF THE TURN MECHANICS
*/

void Track::pastStartCurrentSlowdown(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.2f);
				}
				else {
					v->turn(0.2f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.9f);
				}
				else {
					v->turn(0.9f);
				}
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastTurnExitCurrentSlowDown(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.2f);
				}
				else {
					v->turn(0.2f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}
					
				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastTurnExitCurrentStart(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.2f);
				}
				else {
					v->turn(0.2f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}





void Track::pastSlowDownCurrentTurnIn(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (curGear > PxVehicleGearsData::eFOURTH) {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(0.f);
			v->reverse(1.f);
		}
		else {
			if (angleToTurn < 0) {
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
			v->reverse(0.8f);
			v->forwards(0.f);
		}
	}
	else if (curGear <= PxVehicleGearsData::eSECOND) {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(0.8f);
			v->reverse(0.f);
		}
		else {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
	}
	else {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(0.5f);
			v->reverse(0.f);
		}
		else {
			if (angleToTurn < 0) {
				v->turn(-0.7f);
			}
			else {
				v->turn(0.7f);
			}
			v->reverse(0.f);
			if (std::abs(angleToTurn) > 90.f) {
				v->forwards(0.7f);
			}
			else {
				v->forwards(0.4f);
			}
			
		}
	}
}

void Track::pastTurnInCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastMajorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFIFTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}


void Track::pastTurnInCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
	
}
void Track::pastMinorCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFOURTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}

}
void Track::pastMajorCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastMinorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFIFTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}

// Return value of negative means left turn, postive means right turn
float Track::getAngleToTurnBy(TrackDrivingPoint* currentTarget, Vehicle* v) {
	float angle = 0.f;

	PxVec3 target = PxVec3(currentTarget->x, currentTarget->y, currentTarget->z);

	PxQuat vehicleQuaternion = v->GetTransform().q;
	PxVec3 vehiclePosition = v->GetPosition();

	PxVec3 vehicleFront = vehicleQuaternion.getBasisVector2();
	PxVec3 vehicleFrontNormal = vehicleFront.getNormalized();

	PxVec3 vecToFollow = target - vehiclePosition;
	PxVec3 vecToFollowNormal = vecToFollow.getNormalized();

	
	angle = acos(vehicleFrontNormal.dot(vecToFollowNormal));
	angle = angle * (180.f / M_PI);

	//This tries to turn left
	PxVec3 vehicleLeft = vehicleQuaternion.getBasisVector0();
	PxVec3 vehicleLeftNormal = vehicleLeft.getNormalized();
	float leftDot = vehicleLeftNormal.dot(vecToFollowNormal);

	if (leftDot > 0) {
		angle = -1 * angle;
	}
	
	
	return angle;
}