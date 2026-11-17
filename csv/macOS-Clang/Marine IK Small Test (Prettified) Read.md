
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1682 | 0.383905 | 1019.32ms | 18245 | 2560 | 4.0376e+06 | 10344.7 | 2.98645 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.93 | 0.346415 | 1113.87ms | 18245 | 1280 | 1.68371e+06 | 10469.6 | 1.66674 | 2(Loss) | true |
| Glaze | 1109.17 | 0.601329 | 1580.45ms | 18245 | 160 | 1.42375e+06 | 15687.2 | 0.854954 | 3(Loss) | true |
| simdjson (ondemand) | 1071.68 | 0.193615 | 1623.41ms | 18245 | 4890 | 4.83219e+06 | 16236 | 1.22847 | 4(Loss) | true |
