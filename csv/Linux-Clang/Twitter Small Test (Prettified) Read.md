
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2508.22 | 0.106093 | 150.427ms | 3808 | 160 | 377.531 | 1447.88 | 0.125027 | 0.967145 | 1(Win) | true |
| Glaze | 2110.65 | 0.0710229 | 179.718ms | 3808 | 30 | 44.8 | 1720.6 | 0.230009 | 1.15342 | 2(Loss) | true |
| Jsonifier | 1824 | 0.0785253 | 209.531ms | 3808 | 160 | 391.094 | 1991 | 0.0829417 | 1.33873 | 3(Loss) | true |
| simdjson (ondemand) | 1195.73 | 0.0611138 | 304.166ms | 3808 | 40 | 137.804 | 3037.12 | 0.125236 | 2.04883 | 4(Loss) | true |
