
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2295.28 | 0.366741 | 7443.01ms | 360584 | 40 | 1.20759e+07 | 149820 | 0.894382 | 1.07832 | 1(Win) | true |
| simdjson (ondemand) | 2263 | 0.1478 | 7731.75ms | 360584 | 160 | 8.07079e+06 | 151958 | 0.378544 | 1.09378 | 2(Loss) | true |
