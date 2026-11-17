
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8698.1 | 0.117155 | 771.077ms | 3223 | 40 | 6.85577 | 353.375 | 0.324122 | 0.649721 | 2.19516 | 0.372014 | 0.00031027 | 0 | 0 | 1(Win) | true |
| Glaze | 3263.65 | 0.256857 | 829.41ms | 3223 | 2560 | 14980.8 | 941.795 | 0.137058 | 1.62257 | 4.65109 | 0.652527 | 0.000329783 | 3.51478e-05 | 1.33319e-06 | 2(Loss) | true |
