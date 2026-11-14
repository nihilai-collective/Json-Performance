
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.65 | 0.0581916 | 912.037ms | 3370 | 1280 | 1457.46 | 1833.72 | 0.0583342 | 3.00365 | 12.1599 | 2.30623 | 0.00351748 | 4.47422e-05 | 1.11276e-05 | 1(Win) | true |
| simdjson (ondemand) | 1006.13 | 0.031314 | 1048.05ms | 3370 | 2560 | 2561.32 | 3194.29 | 0.00508695 | 5.18238 | 22.7018 | 4.24807 | 0.00869923 | 8.12546e-05 | 3.82511e-05 | 2(Loss) | true |
