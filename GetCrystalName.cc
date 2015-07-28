int
PHG4CrystalCalorimeterSteppingAction::WhatAreYou(G4TouchableHandle touch, int& j, int& k)
{
	int j_0, k_0;           //The k and k indices for the crystal within the 2x2 matrix
	int j_1, k_1;           //The k and k indices for the 2x2 within the 4x4
	int j_2, k_2;           //The k and k indices for the 4x4 within the mother volume
	//int j, k;             //The final indices of the crystal

	G4VSolid crystal = touch.GetSolid(0);		//Get the crystal solid
	G4VSolid TwoByTwo = touch.GetSolid(1);		//Get the 2x2 solid
	G4VSolid FourByFour = touch.GetSolid(2);	//Get the 4x4 solid

	int prefix = _crystallogicnameprefix.size();
	prefix--;               //Subtracts 1 from the size of the _crystallogicnameprefix, because numbering starts at 0

	string crystal_name = crystal->GetName();               //should be of the form "[PREFIX]_j_0_k_0"
	j_0 = crystal_name[prefix + 4];
	k_0 = crystal_name[prefix + 8];

	string TwoByTwo_name = TwoByTwo->GetName();             //should be of the form TwoByTwo_j_[j_idx]_k_[k_idx]
	j_1 = TwoByTwo_name[11];
	k_1 = TwoByTwo_name[15];

	string FourByFour_name = FourByFour->GetName();         //FourByFour_j_[j_idx]_k_[k_idx]
	j_2 = FourByFour_name[13];
	k_2 = FourByFour_name[17];

	j = j_0 + j_1 + j_2;
	k = k_0 + k_1 + k_2;

	ostringstream NameString;
	NameString.str("");
	NameString << _crystallogicnameprefix << "_j_" << j << "_k_" << k;
	//name = NameString;

	//return NameString;
	return 0;
}





void
PHG4CrystalCalorimeterSteppingAction::CarbonFiberAdjustments(G4double& carbon_fiber_adjust_width, G4double& carbon_fiber_adjust_length)
{
	G4double carbon_fiber_adjust_width = 0.1258525627*mm;	//Because the crystals are slightly angled, the carbon fiber needs to be shortened
	G4double carbon_fiber_adjust_length = 2.4824474402*mm;	//      from the mother volume (to prevent clipping) by this amount.
}



void
PHG4CrystalCalorimeterSteppingAction::CarbonFiberSpacing(G4double& carbon_fiber_width, G4double& air_gap_carbon_fiber, G4double& air_gap_crystals)
{
        //Parameters of the spacing given by PANDA document arXiv:0810.1216v1 Fig. 7.25
        G4double carbon_fiber_width = 0.18*mm;		//Width of the carbon fiber which surrounds the crystal
        G4double air_gap_carbon_fiber = 0.24*mm;	//Air gap between crystal and the carbon fiber
        G4double air_gap_crystals = 0.60*mm;		//Air gap between crystal and crystal
}
