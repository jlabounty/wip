int
GarbageDisposal()
{
	//***************
	//Backward Endcap
	//***************

	G4double placeInZ = -(99-25)*cm;
	G4double placeInY = 0;
	G4double placeInX = 0;
	
	G4double rMin1 = 0*mm;
	G4double rMax1 = 10000*mm;
	G4double rMin2 = 0*mm;
	G4double rMax2 = 20000*mm;
	G4double dZ = 1000*mm;
	G4double sPhi = 0;
	G4double dPhi = 2*M_PI;

	G4Material* material_crystal = G4Material::GetMaterial("G4_PBWO4");
	
	G4VSolid* GarbageCollector_solid = new G4Cons("GarbageCollector_solid",
						rMin1, rMax1,
						rMin2, rMax2,
						dZ/2.,
						sPhi, dPhi );
	G4LogicalVolume* GarbageCollector_logical =  new G4LogicalVolume(GarbageCollector_solid, material_crystal, G4String("GarbageCollector"), 0, 0, 0);

	G4VisAttributes* ecalVisAtt = new G4VisAttributes();
	ecalVisAtt->SetVisibility(false);
	ecalVisAtt->SetForceSolid(false);
	ecalVisAtt->SetColour(G4Colour::Magenta());
	GarbageCollector_logical->SetVisAttributes(ecalVisAtt);

	G4RotationMatrix ecal_rotm;
	ecal_rotm.rotateX(0);
	ecal_rotm.rotateY(0);
	ecal_rotm.rotateZ(0);

	new G4PVPlacement( G4Transform3D(ecal_rotm, G4ThreeVector(placeInX, placeInY, PlaceInZ) ),
		GarbageCollector_logical, 
		"GarbageCollector", 
		logicWorld, 
		0, 
		false, 
		overlapcheck);

	//*****************************
	//Cylinder Surrounding Detector
	//*****************************

	G4double cyl_place = -99*cm;
	G4double r_min = (1*m) + (1*mm);
	G4double r_max = r_min + 1*mm;
	G4double dZ_cyl = 1*m;


	G4VSolid* GarbageCollector_cyl_solid = new G4Tubs("GarbageCollector_cyl_solid",
		r_min,
		r_max,
		dZ_cyl,
		sPhi,
		dPhi);

	G4LogicalVolume* GarbageCollector_cyl_logical = new G4LogicalVolume(GarbageCollector_cyl_solid,
		material_crystal, 
		G4String("GarbageCollector_cyl"), 
		0, 
		0, 
		0);

        GarbageCollector_cyl_logical->SetVisAttributes(ecalVisAtt);

	new G4PVPlacement( G4Transform3D(ecal_rotm, G4ThreeVector(0, 0, cyl_place) ),
		GarbageCollector_cyl_logical,
		"GarbageCollector_cyl",
		logicworld,
		0,
		false,
		overlapcheck);	

}





















