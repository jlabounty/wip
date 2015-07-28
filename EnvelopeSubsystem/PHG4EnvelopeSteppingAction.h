#ifndef PHG4VEnvelopeSteppingAction_h
#define PHG4VEnvelopeSteppingAction_h

#include <g4main/PHG4SteppingAction.h>
#include <Geant4/G4Step.hh>

class PHG4EnvelopeDetector;
class PHG4Hit;
class PHG4HitContainer;

class PHG4EnvelopeSteppingAction : public PHG4SteppingAction
{
	public:
		//Constructor
		PHG4EnvelopeSteppingAction( PHG$EnvelopeDetector* );
	
		//Destructor
		virtual ~PHG4EnvelopeSteppingAction()
		{}
	
		//Stepping Action
		virtual bool UserSteppingAction( const G4Step*, bool);
	
		//reimplemented from base class
		virtual void SetInterfacePointers( PHCompositeNode* );
	
	private:
		
		//pointer to the detector
		PHG4EnvelopeDetector* detector_;
	
		//pointer to hit container
		PHG4HitContainer * hits_;
		PHG4Hit * hit;	
};

#endif //PHG4EnvelopeSteppingAction_h