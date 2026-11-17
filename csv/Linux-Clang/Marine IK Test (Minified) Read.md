
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 783.488 | 0.154332 | 6898.34ms | 1834197 | 80 | 9.49793e+08 | 2.23261e+06 | 0.771349 | 3.1599 | 1(Win) | true |
| Jsonifier (two-stage) | 743.692 | 0.0928288 | 7377.05ms | 1834197 | 80 | 3.81384e+08 | 2.35209e+06 | 0.0515154 | 3.329 | 2(Loss) | true |
| Glaze | 652.275 | 0.35132 | 8431.27ms | 1834197 | 30 | 2.66291e+09 | 2.68173e+06 | 1.66563 | 3.79562 | 3(Loss) | true |
| simdjson (ondemand) | 577.128 | 0.175766 | 9866.01ms | 1834197 | 40 | 1.13521e+09 | 3.03092e+06 | 0.172631 | 4.28967 | 4(Loss) | true |
