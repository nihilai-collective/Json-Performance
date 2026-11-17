
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14700.2 | 0.162264 | 1120.07ms | 58581 | 640 | 24338.1 | 3800.43 | 0.0603187 | 0.345155 | 1.05758 | 0.167614 | 3.52877e-05 | 4.62234e-05 | 3.08334e-05 | 1(Win) | true |
| simdjson (reflection) | 11061.1 | 0.0506124 | 1249.79ms | 58581 | 4890 | 31955 | 5050.78 | 0.449485 | 0.458323 | 1.4967 | 0.212253 | 4.54372e-05 | 4.42364e-05 | 2.78642e-05 | 2(Loss) | true |
| Glaze | 7376.24 | 0.175427 | 1508.04ms | 58581 | 320 | 56492 | 7573.93 | 0.00457964 | 0.688705 | 2.43244 | 0.370342 | 4.85972e-05 | 6.66812e-06 | 2.18714e-06 | 3(Loss) | true |
