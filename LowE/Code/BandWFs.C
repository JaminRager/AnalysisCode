{
    root $GATDIR/LoadGATClasses.C
    GATDataSet* ds = new GATDataSet(25704,25792);
    TChain* gat = ds->GetGatifiedChain();
    TChain* built = ds->GetBuiltChain();
    GATWaveformBrowser browse;
    browse.LoadWaveforms(built, "triTrapMax/trapENFCal>=0.9 && triTrapMax/trapENFCal<=1.1 && wfDCBits");
    browse.GetNWaveforms();
}
