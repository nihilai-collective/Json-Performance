
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1488.25 | 0.204663 | 5152.63ms | 4506447 | 80 | 2.79438e+09 | 2.88774e+06 | 0.660299 | 1.66353 | 1(Win) | true |
| simdjson (ondemand) | 1201.11 | 0.0830428 | 6177.67ms | 4506447 | 30 | 2.64867e+08 | 3.57809e+06 | 0.0939745 | 2.06124 | 2(Loss) | true |
