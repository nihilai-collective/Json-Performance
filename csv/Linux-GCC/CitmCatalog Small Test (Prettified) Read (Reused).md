
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2424.56 | 0.0687261 | 1152.03ms | 9739 | 1280 | 8871.91 | 3830.73 | 0.0407516 | 2.14483 | 8.94545 | 1.55397 | 0.0013281 | 1.58031e-05 | 3.36919e-06 | 1(Win) | true |
| simdjson (ondemand) | 2352.79 | 0.0968484 | 1157.06ms | 9739 | 80 | 1169.33 | 3947.59 | 0.00855026 | 2.21302 | 9.18434 | 1.44334 | 0.00155945 | 2.3103e-05 | 0 | 2(Loss) | true |
