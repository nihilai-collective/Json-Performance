
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11302.6 | 0.159639 | 793.053ms | 6938 | 4890 | 4270.75 | 585.407 | 0.0483703 | 0.478417 | 1.66388 | 0.29951 | 0.000144664 | 1.57692e-05 | 1.47376e-06 | 1(Win) | true |
| Glaze | 3783.18 | 0.23932 | 911.71ms | 6960 | 2560 | 45133.7 | 1754.49 | 0.407913 | 1.3571 | 3.8717 | 0.645259 | 0.000293923 | 2.78938e-05 | 2.80621e-06 | 2(Loss) | true |
