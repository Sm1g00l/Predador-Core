modded class SCR_CampaignMilitaryBaseComponent : SCR_MilitaryBaseComponent
{
	[Attribute(desc: "Prefab para a tenda", uiwidget: UIWidgets.FileNamePicker, params: "et", category: "Prefab")]
	protected ResourceName m_HQTent_modded;
	//------------------------------------------------------------------------------------------------
	//!
	//! \param[in] prefab
	//! \param[in] position
	//! \param[in] rotation
	//! \param[in] isMainTent
	override void SpawnBuilding(ResourceName prefab, vector position, vector rotation, bool isMainTent = false)
	{
		if (prefab.IsEmpty())
			return;

		if (position == vector.Zero)
			return;
		
		//Using a modded ones
		if( ! m_HQTent_modded.IsEmpty() ){
			prefab = m_HQTent_modded;
		}
		
		EntitySpawnParams params = EntitySpawnParams();
		GetOwner().GetWorldTransform(params.Transform);
		params.TransformMode = ETransformMode.WORLD;
		Math3D.AnglesToMatrix(rotation, params.Transform);
		params.Transform[3] = position;
		
		
		IEntity composition = GetGame().SpawnEntityPrefab(Resource.Load(prefab), null, params);
		
		
		if (!composition)
			return;

		if (isMainTent)
		{
			m_HQTent = composition;

			// Delayed call so the supplies system has time to process all the containers first
			if (m_fStartingSupplies >= 0)
				GetGame().GetCallqueue().CallLater(SetInitialSupplies, SCR_GameModeCampaign.MEDIUM_DELAY, false, m_fStartingSupplies);
		}

		SCR_AIWorld aiWorld = SCR_AIWorld.Cast(GetGame().GetAIWorld());

		if (aiWorld)
			aiWorld.RequestNavmeshRebuildEntity(composition);

		SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(composition.FindComponent(SCR_EditableEntityComponent));
		vector transform[4];

		if (!editableEntity)
		{
			GetOwner().GetTransform(transform);
			SCR_TerrainHelper.SnapToTerrain(transform, composition.GetWorld());
			composition.SetTransform(transform);
			return;
		}

		editableEntity.GetTransform(transform);

		if (!SCR_TerrainHelper.SnapToTerrain(transform, composition.GetWorld()))
			return;

		editableEntity.SetTransformWithChildren(transform);
	}
}
