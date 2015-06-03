
int
PHG4CrystalCalorimeterDetector::FillCrystalUnit(G4LogicalVolume *crystal_logic)
{

	//*************************************
	//**********Define Materials***********
	//*************************************
	
	//Crystal Material (Default is Lead Tungstate)
	G4Material* material_crystal = G4Material::GetMaterial(_materialCrystal.c_str());

	//Carbon Fiber
	G4double a = 12.01*g/mole;
	G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
	
	G4double density_carbon_fiber = 0.144*g/cm3;
	G4Material* CarbonFiber = new G4Material(name="CarbonFiber", density, nel=1);
		CarbonFiber->AddElement(elC, 1);
	
	//Air
	G4Material* Air = G4Material::GetMaterial("G4_AIR");

	
	//*************************************
	//**********Build First Crystal********
	//*************************************
	
	//Crystal Dimensions determined by the _dx_front, with 0.18 subtracted out from all sides for carbon fiber
	G4double carbon_fiber_width = 0.18*mm
	G4double air_gap_carbon_fiber = 0.24*mm 										//Air gap between crystal and the carbon fiber
	G4double air_gap_crystals = 0.60*mm												//Air gap between crystal and crystal
	G4double dx_front_small = ( _dx_front - (2.0 * carbon_fiber_width ) ) / 4.0;	
	G4double dy_front_small = ( _dy_front - (2.0 * carbon_fiber_width ) ) / 4.0;	
	G4double dx_back_small = ( _dx_back - (2.0 * carbon_fiber_width ) ) / 4.0;	
	G4double dy_back_small = (_dy_back - (2.0 * carbon_fiber_width ) ) / 4.0;
	G4double dz = _dz_crystal;
	
	//Vertices of the primary crystal
	std::vector<G4TwoVector> vertices;
	vertices.push_back(G4TwoVector( 0, 0));
	vertices.push_back(G4TwoVector( 0,  dy_back_small));
	vertices.push_back(G4TwoVector(  dx_back_small,  dy_back_small));
	vertices.push_back(G4TwoVector(  dx_back_small, 0));
 	vertices.push_back(G4TwoVector( 0, 0));
	vertices.push_back(G4TwoVector( 0,  dy_front_small));
	vertices.push_back(G4TwoVector(  dx_front_small,  dy_front_small));
	vertices.push_back(G4TwoVector(  dx_front_small, 0));
 	
	//Create the primary, irregularly shaped crystal
	G4VSolid* crystal_solid_small = new G4GenericTrap( G4String("eEcal_crystal"), 
												dz,
												vertices );
	
	G4LogicalVolume *crystal_logic_small = new G4LogicalVolume( crystal_solid_small,
												material_crystal,
												"eEcal_crystal",
												0, 0, 0);
	
	G4VisAttributes *visattchk_2 = new G4VisAttributes();
	visattchk_2->SetVisibility(true);
	visattchk_2->SetForceSolid(true);
	visattchk_2->SetColour(G4Colour::Cyan());
	crystal_logic_small->SetVisAttributes(visattchk_2);
	
	//Create the carbon fiber backbone to surround the primary, irregularly shaped crystal on the sloping sides

	//Carbon fiber with same vertices as the primary crystal
	std::vector<G4TwoVector> vertices_carbon_small;
	vertices_carbon_small.push_back(G4TwoVector( 0, 0));
	vertices_carbon_small.push_back(G4TwoVector( 0,  dy_back_small));
	vertices_carbon_small.push_back(G4TwoVector(  dx_back_small,  dy_back_small));
	vertices_carbon_small.push_back(G4TwoVector(  dx_back_small, 0));
 	vertices_carbon_small.push_back(G4TwoVector( 0, 0));
	vertices_carbon_small.push_back(G4TwoVector( 0,  dy_front_small));
	vertices_carbon_small.push_back(G4TwoVector(  dx_front_small,  dy_front_small));
	vertices_carbon_small.push_back(G4TwoVector(  dx_front_small, 0));
	
	G4VSolid* carbon_solid_small = new G4GenericTrap( G4String("carbon_solid_small"), 
												dz,
												vertices_carbon_small );
	
	//Carbon fiber with larger dimensions (vertices + carbon fiber)
	std::vector<G4TwoVector> vertices_carbon_large;
	vertices_carbon_large.push_back(G4TwoVector( 0, 0));
	vertices_carbon_large.push_back(G4TwoVector( 0,  dy_back_small));
	vertices_carbon_large.push_back(G4TwoVector(  dx_back_small,  dy_back_small));
	vertices_carbon_large.push_back(G4TwoVector(  dx_back_small, 0));
 	vertices_carbon_large.push_back(G4TwoVector( 0, 0));
	vertices_carbon_large.push_back(G4TwoVector( 0,  dy_front_small));
	vertices_carbon_large.push_back(G4TwoVector(  dx_front_small,  dy_front_small));
	vertices_carbon_large.push_back(G4TwoVector(  dx_front_small, 0));
	
	G4VSolid* carbon_solid_large = new G4GenericTrap( G4String("carbon_solid_large"), 
												dz,
												vertices_carbon_large );
	
	//Use G4SubtractionSolid to subtract 1 from 2
	G4SubtractionSolid* Carbon_Shell = new G4SubtractionSolid(G4String("Carbon_Shell"), 
															  carbon_solid_large,
															  carbon_solid_small);
	G4LogicalVolume *Carbon_Shell = new G4LogicalVolume( Carbon_Shell,
												CarbonFiber,
												"Carbon_Shell",
												0, 0, 0);

	
	//Place the crystal and carbon fiber in the same mother volume
	
	G4VSolid* crystal_with_backing = new G4GenericTrap( G4String("crystal_with_backing"), 
												dz,
												vertices_carbon_large );
	
	G4LogicalVolume *crystal_with_backing = new G4LogicalVolume( crystal_solid_small,
												material_crystal,
												"crystal_with_backing",
												0, 0, 0);
	
	
	
	
	
	
	
	
	
	//Place this new mother volume 16 times in the mother volume (called in function)
	
	
	
	
	
	
	
	
	

	
	//First crystal
	G4ThreeVector Crystal_Center = G4ThreeVector(0*mm, 0*mm, 0*mm);

	G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
	Rot->rotateX(0*rad);
	Rot->rotateY(0*rad);
	Rot->rotateZ(0*rad);
	
	ostringstream crystal_name;
	crystal_name.str("");
	crystal_name << "eEcal_crystal" << "_1";
		
	new G4PVPlacement( Rot, Crystal_Center,
		crystal_logic,
		crystal_name.str().c_str(),
		ecalenvelope,
		0, 0, overlapcheck);
	
	return 0;