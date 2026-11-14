
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.91 | 0.0758174 | 863.873ms | 3370 | 320 | 355.779 | 1390.74 | 0.050981 | 2.29443 | 9.01632 | 1.63056 | 0.000822515 | 3.52374e-05 | 9.273e-07 | 1(Win) | true |
| simdjson (ondemand) | 1997.78 | 0.0675251 | 895.774ms | 3370 | 320 | 377.611 | 1608.72 | 0.0976103 | 2.64318 | 9.77626 | 1.66884 | 0.00354043 | 6.30564e-05 | 1.02003e-05 | 2(Loss) | true |
