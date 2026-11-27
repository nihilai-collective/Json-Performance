
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11653.1 | 0.250462 | 789.778ms | 6938 | 2560 | 5177.35 | 567.795 | 0.199525 | 0.467104 | 1.7188 | 0.260162 | 0.000144866 | 1.6215e-05 | 3.20923e-06 | 1(Win) | true |
| Glaze | 3556.05 | 0.248491 | 924.232ms | 6960 | 2560 | 55073.8 | 1866.56 | 0.0617325 | 1.45454 | 3.8717 | 0.645259 | 0.000292408 | 2.43579e-05 | 5.5563e-06 | 2(Loss) | true |
