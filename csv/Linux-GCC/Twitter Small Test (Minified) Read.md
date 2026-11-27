
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3199.31 | 0.138627 | 808.411ms | 2889 | 160 | 228.032 | 861.175 | 0.211472 | 1.68615 | 5.34199 | 0.917272 | 0.000346141 | 6.92281e-05 | 4.32676e-06 | 1(Win) | true |
| Glaze | 2397.93 | 0.126579 | 835.449ms | 2889 | 80 | 169.215 | 1148.97 | 0.0021759 | 2.22255 | 8.91035 | 1.55625 | 0.000346141 | 8.65351e-06 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 2227.94 | 0.0699597 | 844.16ms | 2889 | 4890 | 3660.08 | 1236.64 | 0.353528 | 2.38109 | 8.27968 | 1.22984 | 0.000350529 | 5.03992e-05 | 9.2021e-06 | 3(Loss) | true |
| simdjson (reflection) | 1901.61 | 0.113407 | 870.397ms | 2889 | 2560 | 6911.42 | 1448.86 | 0.0095181 | 2.77372 | 9.23365 | 1.30357 | 0.00040685 | 6.39549e-05 | 1.35211e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1382.85 | 0.067594 | 922.461ms | 2889 | 1280 | 2321.53 | 1992.39 | 0.165591 | 3.79847 | 12.0654 | 2.39772 | 0.000658749 | 3.86704e-05 | 1.62253e-06 | 5(Loss) | true |
