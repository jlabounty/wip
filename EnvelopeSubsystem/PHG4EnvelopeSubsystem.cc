#include "PHG4EnvelopeSubsystem.h"
#include "PHG4EnvelopeDetector.h"
#include "PHG4EnvelopeSteppingAction.h"

#include <g4main/PHG4HitContainer.h>
#include <fun4all/getClass.h>

#include <Geant4/globals.hh>

#include <sstream>

using namespace std;

PHG4EnvelopeSubsystem::PHG4EnvelopeSubsystem( const std::string &name, const int lyr ):
	PHG4Subsystem( name ),
	detector_( 0 ),
	steppingAction_( NULL ),
	eventAction_(NULL),
	material("G4_PbWO4"),  // default - lead tungstate crystal
	active(1),
	detector_type(name)
{

}

int PHG4EnvelopeSubsystem::Init( PHCompositeNode* topNode )
{
	PHNodeIterator iter( topNode );
	PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode*>(iter.findFirst("PHCompositeNode", "DST" ));

	// create detector
	detector_ = new PHG4CrystalCalorimeterDetector(topNode, Name());
	detector_->SetActive(active);
	detector_->SetAbsorberActive(active);
	detector_->SetGarbageActive(active);
	detector_->OverlapCheck(overlapcheck);
	
	if (active)
	{
		// create hit output node
		ostringstream nodename;
		nodename <<  "G4HIT_ENVELOPE_" << detector_type;
		
		PHG4HitContainer* crystal_hits = findNode::getClass<PHG4HitContainer>(topNode, nodename.str().c_str());
		if (!crystal_hits)
		{
			crystal_hits = new PHG4HitContainer();
			PHIODataNode<PHObject> *hitNode = new PHIODataNode<PHObject>(crystal_hits, nodename.str().c_str(), "PHObject");
			dstNode->addNode(hitNode);
		}

		// create stepping action
		steppingAction_ = new PHG4CrystalCalorimeterSteppingAction(detector_);
	}
	return 0;
}