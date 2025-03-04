//------------------------------------------------------------------------------------------------
modded class SCR_GameModeCampaign : SCR_BaseGameMode
{
	override bool CanPlayerSpawn_S(SCR_SpawnRequestComponent requestComponent, SCR_SpawnHandlerComponent handlerComponent, SCR_SpawnData data, out SCR_ESpawnResult result = SCR_ESpawnResult.SPAWN_NOT_ALLOWED)
	{
		super.CanPlayerSpawn_S(requestComponent, handlerComponent, data, result);
		
		SCR_SpawnPointSpawnData spawnpointSpawnData = SCR_SpawnPointSpawnData.Cast(data);
		
		if (!spawnpointSpawnData)
			return true;

		SCR_PlayerLoadoutComponent loadoutComp = SCR_PlayerLoadoutComponent.Cast(requestComponent.GetPlayerController().FindComponent(SCR_PlayerLoadoutComponent));

		if (!loadoutComp)
			return true;
		
		SCR_PlayerArsenalLoadout loadout = SCR_PlayerArsenalLoadout.Cast(loadoutComp.GetLoadout());
		
		if (!loadout)
			return true;
		
		SCR_SpawnPoint spawnpoint = spawnpointSpawnData.GetSpawnPoint();
		
		if (!spawnpoint)
			return true;
		
		// Spawning on MHQ with custom loadouts is not allowed
		if (spawnpoint.FindComponent(SCR_CampaignMobileAssemblyStandaloneComponent))
		{
			return true;
		}
		
		SCR_CampaignSpawnPointGroup spawnpointCampaign = SCR_CampaignSpawnPointGroup.Cast(spawnpoint);
		
		if (!spawnpointCampaign)
			return true;
		
		IEntity spawnpointParent = spawnpointCampaign.GetParent();
		
		if (!spawnpointParent)
			return true;
		
		SCR_CampaignMilitaryBaseComponent base = SCR_CampaignMilitaryBaseComponent.Cast(spawnpointParent.FindComponent(SCR_CampaignMilitaryBaseComponent));
		
		if (!base)
			return true;
		
		SCR_ServicePointComponent armory = base.GetServiceByType(SCR_EServicePointType.ARMORY);
		
		if (armory)
			return true;

		result = SCR_ESpawnResult.NOT_ALLOWED_NO_ARSENAL;
		return false;
	}
}
