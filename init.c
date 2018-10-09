void main()
{
	Hive ce = CreateHive();
	if (ce)
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits(0.0, 1.0);
	weather.GetRain().SetLimits(0.0, 1.0);
	weather.GetFog().SetLimits(0.0, 0.25);

	weather.GetOvercast().SetForecastChangeLimits(0.0, 0.2);
	weather.GetRain().SetForecastChangeLimits(0.0, 0.1);
	weather.GetFog().SetForecastChangeLimits(0.15, 0.45);

	weather.GetOvercast().SetForecastTimeLimits(1800, 1800);
	weather.GetRain().SetForecastTimeLimits(600, 600);
	weather.GetFog().SetForecastTimeLimits(1800, 1800);

	weather.GetOvercast().Set(Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set(Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set(Math.RandomFloatInclusive(0.0, 0.1), 0, 0);

	weather.SetWindMaximumSpeed(15);
	weather.SetWindFunctionParams(0.1, 0.3, 50);
}

class CustomMission: MissionServer
{
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++) {
			mag = player.GetInventory().CreateInInventory(mag_type);
			player.SetQuickBarEntityShortcut(mag, i + 1, true);
		}

		//player.SetQuickBarEntityShortcut(mag, 1, true);
	}

	EntityAI assault1Class(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("M4A1");
		gun.GetInventory().CreateAttachment("M4_RISHndgrd_Black");
		gun.GetInventory().CreateAttachment("M4_MPBttstck_Black");
		gun.GetInventory().CreateAttachment("ACOGOptic");
		//gun.GetInventory().CreateAttachment("Mag_STANAG_30Rnd");
		addMags(player, "Mag_STANAG_30Rnd", 3);

		return gun;
	}
	EntityAI assault2Class(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("AKM");
		gun.GetInventory().CreateAttachment("AK_WoodBttstck");
		gun.GetInventory().CreateAttachment("AK_WoodHndgrd");
		gun.GetInventory().CreateAttachment("PSO1Optic");
		//gun.GetInventory().CreateAttachment("Mag_AKM_30Rnd");
		addMags(player, "Mag_AKM_30Rnd", 3);

		return gun;
	}

	EntityAI sniperClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("SVD");
		gun.GetInventory().CreateAttachment("PSO1Optic");
		//gun.GetInventory().CreateAttachment("Mag_SVD_10Rnd");
		addMags(player, "Mag_SVD_10Rnd", 3);

		return gun;
	}

	EntityAI smgClass(PlayerBase player)
	{
		EntityAI gun = player.GetHumanInventory().CreateInHands("UMP45");
		gun.GetInventory().CreateAttachment("PistolSuppressor");
		gun.GetInventory().CreateAttachment("M68Optic");
		//gun.GetInventory().CreateAttachment("Mag_UMP_25Rnd");
		addMags(player, "Mag_UMP_25Rnd", 3);

		return gun;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		//
		TStringArray pants = {"Jeans_Black","Jeans_BlueDark","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey"};
        TStringArray shoes = {"AthleticShoes_Black","AthleticShoes_Blue","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","HikingBootsLow_Beige","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Grey","HikingBoots_Black","HikingBoots_Brown","HikingJacket_Black"};
		TStringArray backpack = {"TortillaBag","HuntingBag","SmershBag","AssaultBag_Ttsko","AssaultBag_Black","AssaultBag_Green","CoyoteBag_Brown","CoyoteBag_Green","AliceBag_Green","AliceBag_Black","AliceBag_Camo"};
        TStringArray vest = {"PlateCarrierComplete","HighCapacityVest_Olive","HighCapacityVest_Black"};
		
        TStringArray drink = {"SodaCan_Cola","SodaCan_Kvass","SodaCan_Pipsi","SodaCan_Spite"};
        TStringArray food = {"Worm","SmallGuts","PowderedMilk","PeachesCan","Pear"};
		TStringArray tool = {"OrienteeringCompass","Knife","PurificationTablets","Matchbox"};
		//
		
		player.RemoveAllItems();
		
		player.GetInventory().CreateInInventory(pants.GetRandomElement());
		player.GetInventory().CreateInInventory(shoes.GetRandomElement());
		player.GetInventory().CreateInInventory(backpack.GetRandomElement());
		player.GetInventory().CreateInInventory(vest.GetRandomElement());
		
		player.GetInventory().CreateInInventory(drink.GetRandomElement());
		player.GetInventory().CreateInInventory(food.GetRandomElement());
		player.GetInventory().CreateInInventory(tool.GetRandomElement());
		player.GetInventory().CreateInInventory("FNX45");
		player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
		player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);

		EntityAI primary;
		EntityAI axe = player.GetInventory().CreateInInventory("FirefighterAxe");

		switch (Math.RandomInt(0, 4)) {
			case 0: primary = assault1Class(player); break;
			case 1: primary = assault2Class(player); break;
			case 2: primary = sniperClass(player); break;
			case 3: primary = smgClass(player); break;
		}

		player.LocalTakeEntityToHands(primary);
		player.SetQuickBarEntityShortcut(primary, 0, true);
		player.SetQuickBarEntityShortcut(rags, 4, true);
		player.SetQuickBarEntityShortcut(axe, 5, true);
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
}