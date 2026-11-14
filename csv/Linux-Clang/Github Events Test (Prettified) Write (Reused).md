
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16421 | 0.334177 | 1209.01ms | 78778 | 4890 | 1.14307e+06 | 4575.15 | 0.392801 | 0.31059 | 1.08476 | 0.182069 | 2.83134e-05 | 2.33007e-05 | 1.28808e-05 | 1(Win) | true |
| Glaze | 5205.04 | 0.161422 | 2198.5ms | 78778 | 4890 | 2.65458e+06 | 14433.8 | 0.0736263 | 0.970187 | 2.95713 | 0.474155 | 0.00035545 | 2.63405e-05 | 1.38724e-05 | 2(Loss) | true |
