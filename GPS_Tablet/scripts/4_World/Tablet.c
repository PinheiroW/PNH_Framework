class GPS_Tablet_ColorBase : Clothing
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionTurnOnWhileInHands);
        AddAction(ActionTurnOffWhileInHands);
    }

    override void OnWorkStart()
    {
        super.OnWorkStart();

        SetObjectTexture(0, "GPS_Tablet\\data\\textures\\Screen_Upit ready.paa");
        SetObjectTexture(1, "GPS_Tablet\\data\\textures\\Screen_Upit ready.paa");
    }

    override void OnWorkStop()
    {
        super.OnWorkStop();

        SetObjectTexture(0, "GPS_Tablet\\data\\textures\\hardware_display.edds");
        SetObjectTexture(1, "GPS_Tablet\\data\\textures\\hardware_display.edds");
    }
}