.x $GATDIR/LoadGATClasses.C
GATDataSet* ds = new GATDataSet(20828,20829);
TChain* gat = ds->GetGatifiedChain();
TChain* built = ds->GetBuiltChain();
ds->GetChannelMap()->DumpChannelMap();
gat->Show(0);
gat->Draw("RawWFblOffset", "channel==1330");
GATWaveformBrowser browse;
browse.LoadWaveforms(built,"channel == 692 && RawWFblOffset<-100");
browse.GetNWaveforms();
browse.DrawWaveform(0);
