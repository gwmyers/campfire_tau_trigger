# CAMPFIRE Group Project
## The SU(3) x U(1) tau trigger project

## Data
The original data files are:

|Background|Signal|
|---|---|
|`output_MB80.root`|`ztt_Output.root`|

The flags have different names and different data structure in these two files, so they are reformatted and stored at `./formatted/` as

|Background|Signal|
|---|---|
|`background.root`|`tau_signal.root`|

There are five variables in the new files. They are all single float number, which is the sum of the array from the original data files.

|Variable in reformatted file|(original bkg) sum of |(original sig) sum of |
|---|---|---|
|`L0EM`|`L0CellEt`|`scellsEM0`|
|`L1EM`|`L1CellEt`|`scellsEM1`|
|`L2EM`|`L2CellEt`|`scellsEM2`|
|`L3EM`|`L3CellEt`|`scellsEM3`|
|`LHAD`|`HadCellEt`|`scellsHAD`|
