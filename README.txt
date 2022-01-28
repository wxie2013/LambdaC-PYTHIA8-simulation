->make LcD0ratio
->./run  or python3 slum_sub.py
->./merge

Once the above data production is done, the following following sequencially: 
1. cross_B2Lc.C: inclusive B-hadron, Lc and B->Lc cross section vs. pT, 
2. create_weight.C: create weight for B2Lc from FONLL
3. prompt_ratio.C: prompt ratio in pythia and FONLL
