
----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1343.02 | 0.0347368 | 8601.11ms | 1922245 | 30 | 6.74459e+06 | 1.36498e+06 | 0.212845 | 3.76103 | 13.1325 | 0.653451 | 0.00242577 | 0.0595651 | 6.72304e-05 | 1(Win) | true |
| simdjson (reflection) | 1331.37 | 0.0746034 | 8716.03ms | 1922245 | 160 | 1.68833e+08 | 1.37693e+06 | 0.103148 | 3.80185 | 13.6342 | 1.13437 | 0.00970644 | 0.0528004 | 0.000146489 | 2(Loss) | true |
| Glaze | 1003.33 | 0.2615 | 5408.34ms | 1833577 | 160 | 3.32334e+09 | 1.74283e+06 | 0.225652 | 5.04434 | 16.0427 | 1.0527 | 0.000996836 | 0.0496126 | 6.292e-05 | 3(Loss) | true |
