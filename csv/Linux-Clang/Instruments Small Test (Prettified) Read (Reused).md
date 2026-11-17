
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3035.78 | 0.126003 | 997.621ms | 7932 | 40 | 394.318 | 2491.8 | 0.326671 | 1.69409 | 7.09002 | 1.12468 | 0.000712305 | 2.20625e-05 | 3.15179e-06 | 1(Win) | true |
| Glaze | 2574.64 | 0.197699 | 1040.04ms | 7932 | 2560 | 86373.6 | 2938.09 | 0.0477126 | 1.99724 | 8.50282 | 1.56733 | 0.00146012 | 3.4325e-05 | 1.38876e-05 | 2(Loss) | true |
| Jsonifier | 2170.22 | 0.265288 | 1092.93ms | 7932 | 4890 | 418120 | 3485.61 | 0.263711 | 2.36102 | 7.72882 | 1.72756 | 0.00141164 | 5.59975e-05 | 2.9262e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1147.65 | 0.177831 | 1405.19ms | 7932 | 1280 | 175861 | 6591.32 | 0.0103226 | 4.42933 | 17.1039 | 2.62078 | 0.00170738 | 2.9548e-05 | 7.38701e-06 | 4(Loss) | true |
