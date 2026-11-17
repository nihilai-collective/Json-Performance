
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6666.72 | 0.0970474 | 772.58ms | 3808 | 320 | 89.4308 | 544.734 | 0.0373027 | 0.828466 | 3.302 | 0.383403 | 0.000262605 | 4.1032e-06 | 0 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 6550.16 | 0.114915 | 771.952ms | 3808 | 320 | 129.895 | 554.428 | 0.103041 | 0.849186 | 3.302 | 0.383403 | 0.000787815 | 1.31303e-05 | 8.20641e-07 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6532.21 | 0.17306 | 776.082ms | 3808 | 4890 | 4526.64 | 555.952 | 0.059298 | 0.843771 | 3.31119 | 0.33167 | 0.000638469 | 2.26624e-05 | 9.55904e-06 | 2(Tie) | true |
| simdjson (reflection) | 6491.94 | 0.258086 | 777.927ms | 3808 | 80 | 166.749 | 559.4 | 0.160628 | 0.858682 | 3.29333 | 0.336134 | 0.000810793 | 2.62605e-05 | 0 | 4(Loss) | true |
| Glaze | 3511.62 | 0.063028 | 817.371ms | 3808 | 4890 | 2077.57 | 1034.16 | 0.054038 | 1.51875 | 6.58508 | 1.20746 | 0.000269425 | 1.68089e-05 | 8.96831e-06 | 5(Loss) | true |
