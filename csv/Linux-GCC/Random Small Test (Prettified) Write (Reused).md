
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 28376.3 | 0.18153 | 750.363ms | 9255 | 160 | 51.0107 | 311.044 | 0.223538 | 0.20481 | 0.871637 | 0.130308 | 0.000108725 | 2.70124e-05 | 9.45435e-06 | 1(Win) | true |
| Glaze | 5355.15 | 0.0988261 | 887.021ms | 9255 | 4890 | 12973.6 | 1648.18 | 0.293582 | 0.982375 | 4.47315 | 0.737007 | 0.000181674 | 3.07356e-05 | 1.28378e-05 | 2(Loss) | true |
| simdjson (reflection) | 516.241 | 0.0979666 | 2451.71ms | 9255 | 4890 | 1.37187e+06 | 17097.1 | 0.0663099 | 9.85527 | 38.0823 | 7.28282 | 0.0216418 | 0.000136708 | 8.64177e-05 | 3(Loss) | true |
