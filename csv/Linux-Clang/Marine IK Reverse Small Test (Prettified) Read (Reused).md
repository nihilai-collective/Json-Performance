
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2737.55 | 0.258817 | 1462.65ms | 18245 | 640 | 173193 | 6355.97 | 0.0673862 | 1.85963 | 7.50271 | 1.39359 | 0.00171203 | 1.47301e-05 | 5.56659e-06 | 1(Win) | true |
| Jsonifier | 2386.45 | 0.155091 | 1558.86ms | 18245 | 1280 | 163669 | 7291.09 | 0.499093 | 2.13413 | 8.09663 | 1.84105 | 0.00215813 | 1.61859e-05 | 4.75301e-06 | 2(Loss) | true |
| Glaze | 2073.9 | 0.0520884 | 1666.66ms | 18245 | 4890 | 93390.7 | 8389.88 | 0.158548 | 2.44955 | 10.7292 | 2.13642 | 0.00325025 | 1.96485e-05 | 7.45365e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2021.84 | 0.0725695 | 1707.47ms | 18245 | 2560 | 99848.2 | 8605.9 | 0.298646 | 2.52382 | 10.3568 | 1.67916 | 0.00201791 | 2.38293e-05 | 9.97705e-06 | 4(Loss) | true |
