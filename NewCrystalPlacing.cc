	CrystalDimensions(dx1, dy1, dx2, dy2, dz);              //Fill crystal dimensions with function PHG4CrystalCalorimeterDetector::CrystalDimensions
	
	G4Material* Air = G4Material::GetMaterial("G4_AIR");

	//Create single 4x4 unit

	G4VSolid* crystal_solid = new G4Trd(G4String("eEcal_crystal"),
		dx1,                                            //Half length on the small face in x
		dx2,                                            //Half length on the large face in x
		dy1,                                            //Half length on the small face in y
		dy2,                                            //Half length on the large face in y
		dz);                                            //Half length in z

	G4LogicalVolume *crystal_logic = new G4LogicalVolume( crystal_solid,
		Air,
		"eEcal_crystal_unit",
		0, 0, 0);

	//Create the single 2x2 unit (MappingIndex = 12)

	G4VSolid* 12_solid = new G4Trd(G4String("12_solid"),
		(dx1/2.0),					//Half length on the small face in x
		(dx2/2.0),					//Half length on the large face in x
		(dy1/2.0),					//Half length on the small face in y
		(dy2/2.0),					//Half length on the large face in y
		dz);						//Half length in z

	G4LogicalVolume *12_logic = new G4LogicalVolume( 12_solid,
		Air,
		"12_unit",
		0, 0, 0);

	//Create the double 2x2 unit (i-shaped, MappingIndex = 22)

	G4VSolid* 22_solid = new G4Trd(G4String("22_solid"),
		(dx1/2.0),					//Half length on the small face in x
		(dx2/2.0),					//Half length on the large face in x
		dy1,						//Half length on the small face in y
		dy2,						//Half length on the large face in y
		dz);						//Half length in z

	G4LogicalVolume *22_logic = new G4LogicalVolume( 22_solid,
		Air,
		"22_unit",
		0, 0, 0);
	

	//Create the triple 2x2 unit (L-shaped, MappingIndex = 32)

	G4LogicalVolume *32_logic = new G4LogicalVolume( 32_solid,
		Air,
		"32_unit",
		0, 0, 0);


	G4VisAttributes *visattchk = new G4VisAttributes();
	visattchk->SetVisibility(false);
	visattchk->SetForceSolid(true);
	visattchk->SetColour(G4Colour::Yellow());
	crystal_logic->SetVisAttributes(visattchk);
	12_logic->SetVisAttributes(visattchk);
	22_logic->SetVisAttributes(visattchk);
	32_logic->SetVisAttributes(visattchk);

	Fill4x4Unit(crystal_logic);
	FillSpecialUnit(12_logic);
	FillSpecialUnit(22_logic);
	FillSpecialUnit(32_logic);

	//Second Quadrant
        j = 0;
        while (j_cry > j) {

                MappingIndex = Crystals[j][8];

		j_idx = Crystals[j][0];
		k_idx = Crystals[j][1];
		x_cent = Crystals[j][2] - _place_in_x;
		y_cent = Crystals[j][3] - _place_in_y;
		z_cent = Crystals[j][4] - _place_in_z;  //Coordinate system refers to mother volume, have to subtract out its position in the actual xyz-space
		r_theta = Crystals[j][5];               //Rotation in Horizontal
		r_phi = Crystals[j][6];                 //Rotation in Vertical
		rot_z = Crystals[j][7];

                if( MappingIndex == 16 )
		{
			G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot->rotateX(r_phi*rad);
			Rot->rotateY(r_theta*rad);
			Rot->rotateZ(0*rad);

			name.str("");
			name << "FourByFour" << "_j_" << j_idx << "_k_" << k_idx;

			new G4PVPlacement( Rot, Crystal_Center,
				crystal_logic,
				name.str().c_str(),
				ecalenvelope,
				0, 0, overlapcheck);
		}
		else if (MappingIndex == 32) 
		{
			G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot->rotateX(r_phi*rad);
			Rot->rotateY(r_theta*rad);
			Rot->rotateZ(rot_z*rad);

			name.str("");
			name << "FourByFour" << "_j_" << j_idx << "_k_" << k_idx;

			new G4PVPlacement( Rot, Crystal_Center,
				32_logic,
				name.str().c_str(),
				ecalenvelope,
				0, 0, overlapcheck);

		}
		else if (MappingIndex == 22)
		{

			G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot->rotateX(r_phi*rad);
			Rot->rotateY(r_theta*rad);
			Rot->rotateZ(rot_z*rad);

			name.str("");
			name << "FourByFour" << "_j_" << j_idx << "_k_" << k_idx;

			new G4PVPlacement( Rot, Crystal_Center,
				22_logic,
				name.str().c_str(),
				ecalenvelope,
				0, 0, overlapcheck);
		}
		else if (MappingIndex == 12)
		{

			G4ThreeVector Crystal_Center = G4ThreeVector(x_cent*mm, y_cent*mm, z_cent*mm);

			G4RotationMatrix *Rot = new G4RotationMatrix(); //rotation matrix for the placement of each crystal
			Rot->rotateX(r_phi*rad);
			Rot->rotateY(r_theta*rad);
			Rot->rotateZ(rot_z*rad);

			name.str("");
			name << "FourByFour" << "_j_" << j_idx << "_k_" << k_idx;

			new G4PVPlacement( Rot, Crystal_Center,
				12_logic,
				name.str().c_str(),
				ecalenvelope,
				0, 0, overlapcheck);
		}

                j++;
        }

