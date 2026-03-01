modded class ActionConstructor  {
    override void RegisterActions( TTypenameArray actions ) {
        super.RegisterActions( actions );
        actions.Insert( ActionTurn_FMReceiver_On );
        actions.Insert( ActionTurn_FMReceiver_Off );
    }
}
