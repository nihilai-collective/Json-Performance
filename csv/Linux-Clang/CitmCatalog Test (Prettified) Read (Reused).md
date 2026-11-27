
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2860.51 | 0.0486122 | 5446.15ms | 1151920 | 640 | 2.23064e+07 | 384043 | 0.478224 | 1.77186 | 8.06799 | 1.32322 | 0.00546457 | 0.0324188 | 1.72511e-05 | 1(Win) | true |
| simdjson (ondemand) | 2653.23 | 0.421155 | 5852.49ms | 1151920 | 80 | 2.43259e+08 | 414046 | 0.903536 | 1.91001 | 8.28432 | 1.2149 | 0.00751976 | 0.0331357 | 1.66353e-05 | 2(Loss) | true |
