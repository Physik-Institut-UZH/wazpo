//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 16 15:43:15 2018 by ROOT version 6.14/04
// from TTree T1/
// found on file: processed_kryton_test_181108.root
//////////////////////////////////////////////////////////

#ifndef branchHolder_h
#define branchHolder_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

using namespace std;

class branchHolder {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventNumber;
   Double_t        Time;
   vector<int>     *BaselineSamplesLeft;
   vector<int>     *BaselineSamplesRight;
   vector<double>  *Baseline;
   vector<double>  *RMS;
   vector<double>  *Threshold;
   vector<double>  *TotalIntegralWaveform;
   vector<vector<double> > *Entropy;
   vector<unsigned short> *NumberPeaks;
   vector<vector<int> > *PeakDistance;
   vector<vector<double> > *PeakArea;
   vector<vector<double> > *PeakHeight;
   vector<vector<unsigned int> > *PeakPosition;
   vector<vector<unsigned int> > *PeakWidth;
   vector<vector<unsigned int> > *PeakWidth10;
   vector<vector<unsigned int> > *PeakWidth50;
   vector<vector<unsigned int> > *PeakLeftEdge;
   vector<vector<unsigned int> > *PeakRightEdge;
   vector<vector<double> > *Risetime;
   vector<vector<double> > *AoP;

   // List of branches
   TBranch        *b_evtnb;   //!
   TBranch        *b_Time;   //!
   TBranch        *b_BaselineSamplesLeft;   //!
   TBranch        *b_BaselineSamplesRight;   //!
   TBranch        *b_Baseline;   //!
   TBranch        *b_RMS;   //!
   TBranch        *b_Threshold;   //!
   TBranch        *b_TotalIntegralWaveform;   //!
   TBranch        *b_Entropy;   //!
   TBranch        *b_NumberPeaks;   //!
   TBranch        *b_PeakDistance;   //!
   TBranch        *b_PeakArea;   //!
   TBranch        *b_PeakHeight;   //!
   TBranch        *b_PeakPosition;   //!
   TBranch        *b_PeakWidth;   //!
   TBranch        *b_PeakWidth10;   //!
   TBranch        *b_PeakWidth50;   //!
   TBranch        *b_PeakLeftEdge;   //!
   TBranch        *b_PeakRightEdge;   //!
   TBranch        *b_Risetime;   //!
   TBranch        *b_AoP;   //!

   branchHolder(TTree *tree=0);
   virtual ~branchHolder();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef branchHolder_cxx
branchHolder::branchHolder(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("processed_kryton_test_181108.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("processed_kryton_test_181108.root");
      }
      f->GetObject("T1",tree);

   }
   Init(tree);
}

branchHolder::~branchHolder()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t branchHolder::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t branchHolder::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void branchHolder::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   BaselineSamplesLeft = 0;
   BaselineSamplesRight = 0;
   Baseline = 0;
   RMS = 0;
   Threshold = 0;
   TotalIntegralWaveform = 0;
   Entropy = 0;
   NumberPeaks = 0;
   PeakDistance = 0;
   PeakArea = 0;
   PeakHeight = 0;
   PeakPosition = 0;
   PeakWidth = 0;
   PeakWidth10 = 0;
   PeakWidth50 = 0;
   PeakLeftEdge = 0;
   PeakRightEdge = 0;
   Risetime = 0;
   AoP = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_evtnb);
   fChain->SetBranchAddress("Time", &Time, &b_Time);
   fChain->SetBranchAddress("BaselineSamplesLeft", &BaselineSamplesLeft, &b_BaselineSamplesLeft);
   fChain->SetBranchAddress("BaselineSamplesRight", &BaselineSamplesRight, &b_BaselineSamplesRight);
   fChain->SetBranchAddress("Baseline", &Baseline, &b_Baseline);
   fChain->SetBranchAddress("RMS", &RMS, &b_RMS);
   fChain->SetBranchAddress("Threshold", &Threshold, &b_Threshold);
   fChain->SetBranchAddress("TotalIntegralWaveform", &TotalIntegralWaveform, &b_TotalIntegralWaveform);
   fChain->SetBranchAddress("Entropy", &Entropy, &b_Entropy);
   fChain->SetBranchAddress("NumberPeaks", &NumberPeaks, &b_NumberPeaks);
   fChain->SetBranchAddress("PeakDistance", &PeakDistance, &b_PeakDistance);
   fChain->SetBranchAddress("PeakArea", &PeakArea, &b_PeakArea);
   fChain->SetBranchAddress("PeakHeight", &PeakHeight, &b_PeakHeight);
   fChain->SetBranchAddress("PeakPosition", &PeakPosition, &b_PeakPosition);
   fChain->SetBranchAddress("PeakWidth", &PeakWidth, &b_PeakWidth);
   fChain->SetBranchAddress("PeakWidth10", &PeakWidth10, &b_PeakWidth10);
   fChain->SetBranchAddress("PeakWidth50", &PeakWidth50, &b_PeakWidth50);
   fChain->SetBranchAddress("PeakLeftEdge", &PeakLeftEdge, &b_PeakLeftEdge);
   fChain->SetBranchAddress("PeakRightEdge", &PeakRightEdge, &b_PeakRightEdge);
   fChain->SetBranchAddress("Risetime", &Risetime, &b_Risetime);
   fChain->SetBranchAddress("AoP", &AoP, &b_AoP);
   Notify();
}

Bool_t branchHolder::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void branchHolder::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t branchHolder::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef branchHolder_cxx
