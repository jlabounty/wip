int
PHG4CrystalCalorimeterDetector::FillSpecialUnit(G4LogicalVolume *crystal_logic, G4int ident)
{

	//*************************************
	//**********Define Materials***********
	//*************************************
	
	//Crystal Material (Default is Lead Tungstate)
	G4Material* material_crystal = G4Material::GetMaterial(_materialCrystal.c_str());

	//Carbon Fiber
	G4double a = 12.01*g/mole;
	G4Element* elC = new G4Element("Carbon", "C", 6., a);
	
	G4double density_carbon_fiber = 0.144*g/cm3;
	G4Material* CarbonFiber = new G4Material("CarbonFiber", density_carbon_fiber, 1);
		CarbonFiber->AddElement(elC, 1);
	
	//Air
	G4Material* Air = G4Material::GetMaterial("G4_AIR");

	
	//*************************************
	//**********Build First Crystal********
	//*************************************
	
	//Crystal Dimensions determined by the _dx_front, with various gaps and carbon fiber widths subtracted out

	//Parameters of the spacing given by PANDA document arXiv:0810.1216v1 Fig. 7.25
	G4double carbon_fiber_width = 0.18*mm;													//Width of the carbon fiber which surrounds the crystal
	G4double air_gap_carbon_fiber = 0.24*mm; 												//Air gap between crystal and the carbon fiber
	G4double air_gap_crystals = 0.60*mm;													//Air gap between crystal and crystal

	//Crystal Dimensions
	G4double dx_front_small = ( _dx_front - (2.0 * carbon_fiber_width ) - (2.0 * air_gap_carbon_fiber) - air_gap_crystals ) / 2.0;		//Full width of the front crystal face	
	G4double dy_front_small = ( _dy_front - (2.0 * carbon_fiber_width )  - (2.0 * air_gap_carbon_fiber) - air_gap_crystals ) / 2.0;		//Full height of the front crystal face
	G4double dx_back_small = ( _dx_back - (2.0 * carbon_fiber_width )  - (2.0 * air_gap_carbon_fiber) - air_gap_crystals ) / 2.0;		//Full width of the back crystal face
	G4double dy_back_small = (_dy_back - (2.0 * carbon_fiber_width )  - (2.0 * air_gap_carbon_fiber) - air_gap_crystals ) / 2.0;		//Full height of the back crystal face
	G4double dz = _dz_crystal;

	//Vertices of the primary, irregularly shaped crystal put into a vector
	std::vector<G4TwoVector> vertices;
	vertices.push_back(G4TwoVector( 0, 0));
	vertices.push_back(G4TwoVector( 0,  dy_front_small));
	vertices.push_back(G4TwoVector(  dx_front_small,  dy_front_small));
	vertices.push_back(G4TwoVector(  dx_front_small, 0));
 	vertices.push_back(G4TwoVector( 0, 0));
	vertices.push_back(G4TwoVector( 0,  dy_back_small));
	vertices.push_back(G4TwoVector(  dx_back_small,  dy_back_small));
	vertices.push_back(G4TwoVector(  dx_back_small, 0));
 	
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
	
	//****************************************************
	//Build the solid/logical volume for the 2 x 2 crystal
	//****************************************************

	G4double TwoByTwo_dx1 = ( (2.0 * dx_front_small) + (2.0 * air_gap_carbon_fiber) + air_gap_crystals ) / 2.0;
	G4double TwoByTwo_dx2 = ( (2.0 * dx_back_small) + (2.0 * air_gap_carbon_fiber) + air_gap_crystals ) / 2.0;
	G4double TwoByTwo_dy1 = TwoByTwo_dx1;
	G4double TwoByTwo_dy2 = TwoByTwo_dx2;
	G4double TwoByTwo_dz = _dz_crystal; 

	G4VSolid* Two_by_Two_solid = new G4Trd(G4String("Two_by_Two_solid"),
		TwoByTwo_dx1,						//Half length on the small face in x
		TwoByTwo_dx2,						//Half length on the large face in x
		TwoByTwo_dy1,						//Half length on the small face in y
		TwoByTwo_dy2,						//Half length on the large face in y
		TwoByTwo_dz);						//Half length in z

        G4LogicalVolume *Two_by_Two_logic = new G4LogicalVolume( Two_by_Two_solid,
                Air,
                "2_by_2_unit",
                0, 0, 0);
	
	G4VisAttributes *visattchk_4 = new G4VisAttributes();
	visattchk_4->SetVisibility(false);
	visattchk_4->SetForceSolid(true);
	visattchk_4->SetColour(G4Colour::Grey());
	Two_by_Two_logic->SetVisAttributes(visattchk_4);
	
	
	//*************************************************************
	//Read in mapping file for a single 2 x 2 block and 4 x 4 block
	//*************************************************************
	
	//The first four lines of the data file refer to the 2x2 block, and the last four lines refer to the mapping of the 4x4 block

	const string Crystal_Mapping_Small = _inputFile_4x4_construct;		//Get the mapping file for the 4 x 4 block
	const int NumberOfIndices = 9; 						//Number of indices in mapping file for 4x4 block

        ifstream datafile_2;

	//Open the datafile, if it won't open return an error
        if (!datafile_2.is_open())
        {
                datafile_2.open(Crystal_Mapping_Small.c_str());
                if(!datafile_2)
                {
                        cerr << endl << "*******************************************************************" << endl;
                        cerr << "ERROR in 2 by 2 crystal mapping"; 
			cerr << "Failed to open " << Crystal_Mapping_Small <<" --- Exiting program." << endl;
                        cerr << "*******************************************************************" << endl << endl;
                        exit(1);
                }
        }

	//Find the number of lines in the file, make and fill a NumberOfLines by NumberOfIndices matrix with contents of data file
	int NumberOfLines = 0;
        ifstream in(Crystal_Mapping_Small.c_str());
        std::string unused;
        while ( std::getline(in, unused) )
           ++NumberOfLines;

	G4int j_cry = NumberOfLines;
	G4int k_cry = NumberOfIndices;

	double TwoByTwo[j_cry][k_cry];

	G4int j = 0;
        G4int k = 0;

        while (j_cry > j) {
                while (k_cry > k) {
                        datafile_2 >> TwoByTwo[j][k];
                        k++;
                }
                j++;
                k = 0;
        }

	//**************************************************	
	//Place the single crystal in the 2x2 volume 4 times
	//**************************************************	
	
	G4int j_idx, k_idx;
	G4double x_cent, y_cent, z_cent, rot_x, rot_y, rot_z;
	G4int MappingIndex;

	j = 0;
	while (j_cry > j) {
		MappingIndex = TwoByTwo[j][8];		
		if (MappingIndex == 1) {
			j_idx = TwoByTwo[j][0];
			k_idx = TwoByTwo[j][1];
			x_cent = TwoByTwo[j][2];
			y_cent = TwoByTwo[j][3];
			z_cent = TwoByTwo[j][4];
			rot_x = TwoByTwo[j][5];
			rot_y = TwoByTwo[j][6];
			rot_z = TwoByTwo[j][7];

			G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
				Rot->rotateX(0*rad);
				Rot->rotateY(0*rad);
				Rot->rotateZ(rot_z*rad);

			ostringstream crystal_name;
			crystal_name.str("");
			crystal_name << _crystallogicnameprefix << "_j_"<< j_idx << "_k_" << k_idx;
			
			new G4PVPlacement( Rot, Crystal_Center,
				crystal_logic_small,
				crystal_name.str().c_str(),
				Two_by_Two_logic,
				0, 0, overlapcheck);
			
			j_idx = k_idx = 0;
			x_cent = y_cent = z_cent = rot_x = rot_y = rot_z = 0.0;
		}
		j++;
	}

	//****************************
	//Place the 2x2 Crystal Blocks
	//****************************

	j = 0;
	while (j_cry > j) 
	{
		j_idx = TwoByTwo[j][0];
		k_idx = TwoByTwo[j][1];
		x_cent = TwoByTwo[j][2];
		y_cent = TwoByTwo[j][3];
		z_cent = TwoByTwo[j][4];
		rot_x = TwoByTwo[j][5];
		rot_y = TwoByTwo[j][6];
		rot_z = TwoByTwo[j][7];
		MappingIndex = TwoByTwo[j][8];		

		if (ident == 12) 
		{
			G4ThreeVector Crystal_Center = G4ThreeVector(0*mm, 0*mm, 0*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix();
				Rot->rotateX(0*rad);
				Rot->rotateY(0*rad);
				Rot->rotateZ(0*rad);

			ostringstream Two_by_Two_name;
			Two_by_Two_name.str("");
			Two_by_Two_name << "TwoByTwo" << "_j_"<< 0 << "_k_" << 0;
		
			new G4PVPlacement( Rot, Crystal_Center,
				Two_by_Two_logic,
				Two_by_Two_name.str().c_str(),
				crystal_logic,
				0, 0, overlapcheck);

		}
		else if (ident == 22)
		{
			if (MappingIndex == 22) 
			{
				G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

				G4RotationMatrix *Rot = new G4RotationMatrix();
					Rot->rotateX(rot_x*rad);
					Rot->rotateY(rot_y*rad);
					Rot->rotateZ(0*rad);

				ostringstream Two_by_Two_name;
				Two_by_Two_name.str("");
				Two_by_Two_name << "TwoByTwo" << "_j_"<< j_idx << "_k_" << k_idx;
			
				new G4PVPlacement( Rot, Crystal_Center,
					Two_by_Two_logic,
					Two_by_Two_name.str().c_str(),
					crystal_logic,
					0, 0, overlapcheck);
			}
			
		}
		else if (ident == 32)
		{
			if (MappingIndex == 32) 
			{
				G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

				G4RotationMatrix *Rot = new G4RotationMatrix();
					Rot->rotateX(rot_x*rad);
					Rot->rotateY(rot_y*rad);
					Rot->rotateZ(0*rad);

				ostringstream Two_by_Two_name;
				Two_by_Two_name.str("");
				Two_by_Two_name << "TwoByTwo" << "_j_"<< j_idx << "_k_" << k_idx;
			
				new G4PVPlacement( Rot, Crystal_Center,
					Two_by_Two_logic,
					Two_by_Two_name.str().c_str(),
					crystal_logic,
					0, 0, overlapcheck);
			}
		}
		else
		{
			cerr << endl << "Invalid Mapping Type: " << ident << endl;
			return -1;
		}
		
		j_idx = k_idx = 0;
		x_cent = y_cent = z_cent = rot_x = rot_y = rot_z = 0.0;
		j++;
	}

	//*******************
	//Create Carbon Fiber
	//*******************

	G4VSolid *Carbon_hunk_solid = crystal_logic->GetSolid()

	if (ident == 12) 
	{
		x_cent = 0*mm;
		y_cent = 0*mm;
		z_cent = 0*mm;
		rot_x = 0*mm;
		rot_y = 0*mm;
		rot_z = 0*mm;

		G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

		G4RotationMatrix *Rot_1 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot_1->rotateX(rot_x*rad);
			Rot_1->rotateY(rot_y*rad);
			Rot_1->rotateZ(rot_z*rad);

		G4SubtractionSolid* Carbon_Shell_solid = new G4SubtractionSolid(G4String("Carbon_Shell_solid"),
									Carbon_hunk_solid,
									Two_by_Two_solid,
									Rot_1,
									Crystal_Center);
	}
	else if (ident == 22)
	{

		j = 0;
		G4int counter = 0;
		while (j_cry > counter) 
		{
			MappingIndex = TwoByTwo[j][8];		
			if (MappingIndex != 22) j++;
			counter++;
		}

		//First Hole
	
		x_cent = TwoByTwo[j][2];
		y_cent = TwoByTwo[j][3];
		z_cent = TwoByTwo[j][4];
		rot_x = TwoByTwo[j][5];
		rot_y = TwoByTwo[j][6];
		rot_z = TwoByTwo[j][7];
	
		G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

		G4RotationMatrix *Rot_1 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot_1->rotateX(rot_x*rad);
			Rot_1->rotateY(rot_y*rad);
			Rot_1->rotateZ(0*rad);

		G4SubtractionSolid* Carbon_Shell_1 = new G4SubtractionSolid(G4String("Carbon_Shell_1"),
			Carbon_hunk_solid,
			Two_by_Two_solid,
			Rot_1,
			Crystal_Center);

		j++;

		//Second Hole

		x_cent = TwoByTwo[j][2];
		y_cent = TwoByTwo[j][3];
		z_cent = TwoByTwo[j][4];
		rot_x = TwoByTwo[j][5];
		rot_y = TwoByTwo[j][6];
		rot_z = TwoByTwo[j][7];

		Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

		G4RotationMatrix *Rot_2 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot_2->rotateX(rot_x*rad);
			Rot_2->rotateY(rot_y*rad);
			Rot_2->rotateZ(0*rad);

		G4SubtractionSolid* Carbon_Shell_solid = new G4SubtractionSolid(G4String("Carbon_Shell_solid"),
			Carbon_Shell_1,
			Two_by_Two_solid,
			Rot_2,
			Crystal_Center);
	}
	else if (ident == 32)
	{


	//First 2x2 crystal

	j = 0;
	G4int counter = 0;
	while (j_cry > counter) {
		MappingIndex = TwoByTwo[j][8];		
		if (MappingIndex != 32) j++;
		counter++;
	}

	x_cent = TwoByTwo[j][2];
	y_cent = TwoByTwo[j][3];
	z_cent = TwoByTwo[j][4];
	rot_x = TwoByTwo[j][5];
	rot_y = TwoByTwo[j][6];
	rot_z = TwoByTwo[j][7];

	G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

	G4RotationMatrix *Rot_1 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
		Rot_1->rotateX(rot_x*rad);
		Rot_1->rotateY(rot_y*rad);
		Rot_1->rotateZ(0*rad);

        G4SubtractionSolid* Carbon_Shell_1 = new G4SubtractionSolid(G4String("Carbon_Shell_1"),
								Carbon_hunk_solid,
								Two_by_Two_solid,
								Rot_1,
								Crystal_Center);
	j++;

	//----------------------------------------------------------------------------------------------------
	//Second 2x2 crystal

	x_cent = TwoByTwo[j][2];
	y_cent = TwoByTwo[j][3];
	z_cent = TwoByTwo[j][4];
	rot_x = TwoByTwo[j][5];
	rot_y = TwoByTwo[j][6];
	rot_z = TwoByTwo[j][7];

	Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

	G4RotationMatrix *Rot_2 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
		Rot_2->rotateX(rot_x*rad);
		Rot_2->rotateY(rot_y*rad);
		Rot_2->rotateZ(0*rad);

        G4SubtractionSolid* Carbon_Shell_2 = new G4SubtractionSolid(G4String("Carbon_Shell_2"),
								Carbon_Shell_1,
								Two_by_Two_solid,
								Rot_2,
								Crystal_Center);
	j++;

	//----------------------------------------------------------------------------------------------------
	//Third 2x2 crystal
	
	x_cent = TwoByTwo[j][2];
	y_cent = TwoByTwo[j][3];
	z_cent = TwoByTwo[j][4];
	rot_x = TwoByTwo[j][5];
	rot_y = TwoByTwo[j][6];
	rot_z = TwoByTwo[j][7];

	Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

	G4RotationMatrix *Rot_3 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
		Rot_3->rotateX(rot_x*rad);
		Rot_3->rotateY(rot_y*rad);
		Rot_3->rotateZ(0*rad);

        G4SubtractionSolid* Carbon_Shell_solid = new G4SubtractionSolid(G4String("Carbon_Shell_solid"),
								Carbon_Shell_2,
								Two_by_Two_solid,
								Rot_3,
								Crystal_Center);
	}
	else
	{
		cout << endl << "Something is terribly, terribly wrong... Sorry :)" << endl;
	}

        G4LogicalVolume *Carbon_Shell_logic = new G4LogicalVolume( Carbon_Shell_solid,
                CarbonFiber,
                "Carbon_Fiber_logic",
                0, 0, 0);
	
	G4VisAttributes *visattchk_5 = new G4VisAttributes();
	visattchk_5->SetVisibility(true);
	visattchk_5->SetForceSolid(true);
	visattchk_5->SetColour(G4Colour::Black());
	Carbon_Shell_logic->SetVisAttributes(visattchk_5);

	//*************************************
	//Place the carbon fiber shell at (0,0)
	//*************************************

	G4ThreeVector Carbon_Center = G4ThreeVector(0*mm, 0*mm, 0*mm);

	G4RotationMatrix *Rot_5 = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
		Rot_5->rotateX(0*rad);
		Rot_5->rotateY(0*rad);
		Rot_5->rotateZ(0*rad);

	new G4PVPlacement(Rot_5, Carbon_Center,
		Carbon_Shell_logic,
		"Carbon_Fiber_Shell",
		crystal_logic,
		0, 0, overlapcheck);

	return 0;
}
