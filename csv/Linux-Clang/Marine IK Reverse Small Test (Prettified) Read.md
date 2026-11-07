
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2881.48 | 0.102367 | 606.616ms | 18245 | 4890 | 186848 | 6038.49 | 0.0880253 | 0.855321 | 1(Win) | true |
| Jsonifier | 2415.63 | 0.1127 | 772.555ms | 18245 | 4890 | 322240 | 7202.99 | 0.224306 | 1.02101 | 2(Loss) | true |
| simdjson (ondemand) | 1971.96 | 0.0741651 | 936.471ms | 18245 | 30 | 1284.73 | 8823.6 | 0.00793264 | 1.25204 | 3(Loss) | true |
| Glaze | 1818.19 | 0.154075 | 959.032ms | 18245 | 2560 | 556562 | 9569.83 | 0.0413089 | 1.35795 | 4(Loss) | true |
