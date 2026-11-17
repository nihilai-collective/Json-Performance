
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2869.9 | 0.0406274 | 822.697ms | 2889 | 640 | 97.3595 | 960.02 | 0.144806 | 1.87013 | 6.11769 | 0.996192 | 0.000346141 | 3.51549e-05 | 5.40845e-06 | 1(Win) | true |
| Glaze | 2390.38 | 0.11225 | 837.371ms | 2889 | 320 | 535.656 | 1152.61 | 0.0271051 | 2.23074 | 8.85739 | 1.54552 | 0.000347222 | 7.13915e-05 | 3.1369e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2254.71 | 0.164842 | 848.882ms | 2889 | 80 | 324.594 | 1221.96 | 0.0173931 | 2.31914 | 8.01211 | 1.19315 | 0.000350467 | 5.62478e-05 | 2.59605e-05 | 3(Loss) | true |
| simdjson (reflection) | 1997.5 | 0.0961764 | 867.033ms | 2889 | 2560 | 4505.03 | 1379.3 | 0.00232222 | 2.61896 | 9.23295 | 1.30737 | 0.000418073 | 0.000200248 | 0.000107358 | 4(Loss) | true |
| simdjson (ondemand) | 1359.42 | 0.0639311 | 933.252ms | 2889 | 1280 | 2148.93 | 2026.72 | 0.00543489 | 3.8219 | 12.091 | 2.41537 | 0.00065334 | 0.000180913 | 0.000107358 | 5(Loss) | true |
