int
PHG4CrystalCalorimeterDetector::BuildTracker(G4LogicalVolume* logicWorld) 
{
	//**************
	//Initial Values
	//**************

	const G4double E = 2.718281828459045235360287;

	G4double x_pos = _place_in_x;	
	G4double y_pos = _place_in_y;	
	G4double z_pos = _place_in_z + _dz_crystal;	
	
	G4double eta = -1.2;			//Maximum psuedorapidity of the electromagnetic calorimeter
	G4double theta = 2*atan(E^(-1*eta));	//The angle the outer edge of the calorimeter makes with the interaction point.
	G4double r = z_pos * tan(theta);	//The radius of the electromagnetic calorimeter
	

	//************************
	//Materials of the Tracker
	//************************
	
	G4Material* Air = G4Material::GetMaterial("G4_AIR");

	//******************
	//Build the tracker
	//******************

	G4Solid *Air_Tracker = new G4Tubs("Air_Tracker",
		0*mm,
		r,
		1*mm,
		0*rad,
		2*TMath::PI() );

	//*****************
	//Place the tracker
	//*****************

        z_cent = z_pos - 0.5*mm;

        G4ThreeVector Tracking_Center = G4ThreeVector(x_pos, y_pos, z_cent);

        G4RotationMatrix *Rot = new G4RotationMatrix(); 	//rotation matrix for the placement of the flat piece of tracking material
                Rot_1->rotateX(0*rad);
                Rot_1->rotateY(0*rad);
                Rot_1->rotateZ(0*rad);

	name.str("");
	name << "FourByFour" << "_j_" << j_idx << "_k_" << k_idx;

	new G4PVPlacement( Rot, Tracking_Center,
		logicWorld,
		name.str().c_str(),
		ecalenvelope,
		0, 0, overlapcheck);		


	//****************
	//All Done! Return
	//****************

	return 0;
}

int 
PHG4CrystalCalorimeterDetector::Tracking(const G4Track* aTrack , G4double x_pos, G4double y_pos)
{

	G4TouchableHandle touch = aStep->GetPreStepPoint()->GetTouchableHandle();
	static G4double x_pos_tracking, y_pos_tracking;
	//http://www-geant4.kek.jp/lxr/source//examples/extended/field/field04/src/F04SteppingAction.cc#L79

	if(the track is inside the tracker) 
	{
		x_pos_tracking = aTrack->GetPosition().x(); 
		y_pos_tracking = aTrack->GetPosition().y(); 
	}

	return 0;
}
