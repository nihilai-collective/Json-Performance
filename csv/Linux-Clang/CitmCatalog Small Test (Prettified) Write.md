
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10359.1 | 0.240169 | 799.069ms | 6938 | 2560 | 6024.19 | 638.724 | 0.146318 | 0.519799 | 1.73595 | 0.316085 | 0.000198803 | 1.97621e-05 | 2.70251e-06 | 1(Win) | true |
| Glaze | 3492.11 | 0.223764 | 929.339ms | 6960 | 2560 | 46308.8 | 1900.74 | 0.00731678 | 1.48166 | 4.23262 | 0.722414 | 0.000296336 | 3.5246e-05 | 3.47971e-06 | 2(Loss) | true |
