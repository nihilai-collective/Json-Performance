
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2410.52 | 0.0872753 | 1165.15ms | 9739 | 640 | 7237.18 | 3853.04 | 0.00944782 | 2.15962 | 8.93162 | 1.5517 | 0.00123794 | 8.8401e-05 | 6.12871e-05 | 1(Win) | true |
| simdjson (ondemand) | 2341.82 | 0.0484817 | 1157.95ms | 9739 | 1280 | 4732.45 | 3966.07 | 0.00551584 | 2.22196 | 9.16342 | 1.43665 | 0.00135177 | 3.24886e-05 | 1.00273e-05 | 2(Loss) | true |
