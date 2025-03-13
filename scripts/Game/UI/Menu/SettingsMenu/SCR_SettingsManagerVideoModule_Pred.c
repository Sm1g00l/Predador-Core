/*
modded class SCR_ChimeraCharacter : ChimeraCharacter
{
	override void EOnInit(IEntity owner)
	{
		int dshadows;
		GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Get("DistantShadowsQuality",dshadows);
		//Print("____shad" + dshadows.ToString());
		if (dshadows < 1)
		{
			GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Set("DistantShadowsQuality", 1);
			//GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Get("DistantShadowsQuality",dshadows);
			//Print("____shad" + dshadows.ToString());
			GetGame().UserSettingsChanged();
		};
		super.EOnInit( owner );		
	}
}*/
modded class SCR_BaseGameMode : BaseGameMode
{
	override protected void OnGameModeStart()
	{
		int dshadows;
		int grassLod;
		int grassDistance;
		
		GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Get("DistantShadowsQuality",dshadows);
		GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Get("Lod",grassLod);
		GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Get("Distance",grassDistance);
		
		//if lower than low, override them to the low
		if (dshadows < 1)
		{
			GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Set("DistantShadowsQuality", 1);
			
		};
		
		//if lower than medium, override them to the medium
		if(grassLod < 2)
		{
			GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Set("Lod", 2);
		}	
		
		//if lower than 200, override them to the 200
		if(grassDistance < 200)
		{
			GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Set("Distance", 2);
		}
		GetGame().UserSettingsChanged();
		super.OnGameModeStart();
	}
}

modded class SCR_SettingsSubMenuBase: SCR_SubMenuBase
{
	override protected void OnMenuItemChanged(SCR_SettingsBindingBase binding)
	{
		int dshadows;
		int grassLod;
		int grassDistance;
		
		GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Get("DistantShadowsQuality",dshadows);
		GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Get("Lod",grassLod);
		GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Get("Distance",grassDistance);
		
		//if lower than low, override them to the low
		if (dshadows < 1)
		{
			GetGame().GetEngineUserSettings().GetModule("VideoUserSettings").Set("DistantShadowsQuality", 1);
		};
		
		//if lower than medium, override them to the medium
		if(grassLod < 2)
		{
			GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Set("Lod", 2);
		}	
		
		//if lower than 200, override them to the 200
		if(grassDistance < 200)
		{
			GetGame().GetEngineUserSettings().GetModule("GrassMaterialSettings").Set("Distance", 2);
		}
		
		GetGame().UserSettingsChanged();
		super.OnMenuItemChanged(binding);
	}
};
