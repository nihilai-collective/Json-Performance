
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2349.06 | 0.123301 | 886.212ms | 18245 | 4890 | 407892 | 7407.14 | 0.0181309 | 1(Win) | true |
| Jsonifier | 2275.31 | 0.16007 | 909.479ms | 18245 | 2560 | 383586 | 7647.2 | 0.0392147 | 2(Loss) | true |
| simdjson (reflection) | 2147.62 | 0.117493 | 945.666ms | 18245 | 2560 | 231973 | 8101.9 | 0.00617177 | 3(Loss) | true |
| simdjson (ondemand) | 1508.75 | 0.094313 | 1353.23ms | 18245 | 4890 | 578500 | 11532.6 | 0.210572 | 4(Loss) | true |
| Glaze | 1451.27 | 0.147768 | 1365.66ms | 18245 | 30 | 9416.09 | 11989.3 | 0.42523 | 5(Loss) | true |
