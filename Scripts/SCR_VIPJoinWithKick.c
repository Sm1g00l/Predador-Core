modded class SCR_JoinQueueManagerComponent
{
    protected ref array<string> m_aVIPUIDs = {
        "26b79db7-2157-4b1a-b8d6-9a92ad65803b"
    };

    bool IsVIP(string uid)
    {
        return m_aVIPUIDs.Contains(uid);
    }

    override void AddPlayerToQueue(string uid)
    {
        if (IsVIP(uid) && !CanAcceptMorePlayers())
        {
            PrintFormat("VIP %1 tentou entrar em servidor cheio", uid);

            if (KickNonVIPFor(uid))
            {
                PrintFormat("Slot liberado para VIP %1", uid);
                AcceptPlayer(uid);
                return;
            }
        }

        if (IsVIP(uid))
        {
            m_aJoinQueue.InsertAt(uid, 0);
            Print("VIP entrou na fila: " + uid);
        }
        else
        {
            super.AddPlayerToQueue(uid);
        }
    }

    bool KickNonVIPFor(string incomingVIP)
    {
        array<string> connectedUIDs = GetConnectedPlayerUIDs();

        foreach (string uid : connectedUIDs)
        {
            if (!IsVIP(uid))
            {
                KickPlayer(uid, "Você foi desconectado para liberar espaço para um VIP.");
                return true;
            }
        }

        // Nenhum jogador comum disponível para kick
        return false;
    }

    array<string> GetConnectedPlayerUIDs()
    {
        array<string> uids = {};
        int count = SCR_PlayerManager.GetPlayerCount();
        for (int i = 0; i < count; i++)
        {
            SCR_PlayerController controller = SCR_PlayerManager.GetPlayerController(i);
            if (controller)
            {
                string uid = controller.GetPlayerId();
                if (uid != "")
                    uids.Insert(uid);
            }
        }
        return uids;
    }

    void KickPlayer(string uid, string reason)
    {
        PlayerManager playerManager = GetGame().GetPlayerManager();
        PlayerController controller = playerManager.GetPlayerByUid(uid);
        if (controller)
        {
            controller.Disconnect(reason);
            PrintFormat("Jogador %1 foi kickado: %2", uid, reason);
        }
    }
	
	override void OnPostInit(IEntity owner)
		{
   	 super.OnPostInit(owner);
   	 Print("VIPJoinQueueManager carregado");
		}

}
