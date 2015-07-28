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
	name << "TrackingLayer";

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
PHG4CrystalCalorimeterDetector::SetTracking(const G4Track* aTrack)
{

	static G4double x_pos_tracking = 999999999.0, y_pos_tracking = 999999999.0;
	//http://www-geant4.kek.jp/lxr/source//examples/extended/field/field04/src/F04SteppingAction.cc#L79

	x_pos_tracking = aTrack->GetPosition().x();
	y_pos_tracking = aTrack->GetPosition().y();

	return 0;
}

int PHG4CrystalCalorimeterDetector::FindTracking(G4double& x_pos, G4double& y_pos)
{
	if(x_pos_tracking = 999999999.0 && y_pos_tracking = 999999999.0)
	{
		cerr << endl << "ERROR: NO TRACKING INFORMATION FOUND" << endl;
		return -1;
	}

	x_pos = x_pos_tracking;
	y_pos = y_pos_tracking;

	return 0;
}
