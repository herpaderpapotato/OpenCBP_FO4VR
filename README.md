# OpenCBPC_FO4VR
OpenCBPC Physics for Fallout4VR 
Visual Studio 2022 and later.

This repo is just copy+pasted stuff from:
https://github.com/peteben/OpenCBP_FO4VR/tree/F4VR0 and https://github.com/ericncream/OpenCBP_FO4

Possibly with some code copied from https://github.com/rollingrock/Fallout-4-VR-Body and one of the https://github.com/stickpin2 repo's

So all credit to them.


I made this fork because:

CBP on nexus mods gives me error.
```
plugin C:\Program Files (x86)\Steam\steamapps\common\Fallout 4 VR\Data\F4SE\Plugins\\cbp.dll (00000001 cbpfo4 00000002) reported as incompatible during query
```

OCBPC-0.3-CBBE on ll gives me error.
```
plugin C:\Program Files (x86)\Steam\steamapps\common\Fallout 4 VR\Data\F4SE\Plugins\\cbp.dll (00000001 OCBPC plugin 00000018) reported as incompatible during query
```

OCBP-2.2.5-CBBE on ll gives me error.
```
plugin C:\Program Files (x86)\Steam\steamapps\common\Fallout 4 VR\Data\F4SE\Plugins\\cbp.dll (00000001 OCBP plugin 00000018) reported as incompatible during query
```

OCBP_3.1.2_CBBE on ll gives me error.
```
plugin C:\Program Files (x86)\Steam\steamapps\common\Fallout 4 VR\Data\F4SE\Plugins\\cbp.dll (00000001 OCBP plugin 00000018) reported as incompatible during query
```

Which is all expected because they're not compatibe with F4SE 0.6.21 + F4SELoader 1.72.2, or however the nomenclature goes.

This version with f4sevr_1_2_72.dll and f4sevr_loader.exe version 0.0.6.21 loads successfully with:
```
plugin C:\Program Files (x86)\Steam\steamapps\common\Fallout 4 VR\Data\F4SE\Plugins\\cbp.dll (00000001 OCBP plugin 00000018) loaded correctly
```

Physics and math calculations are unchanged from ocbpc commit. Tested in game with and without FRIK.

If there's any issues, good luck ;). I just compiled it, I don't know how it works.
