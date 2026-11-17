
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2767.45 | 0.119037 | 637.333ms | 18245 | 4890 | 273905 | 6287.3 | 1.29438 | 0.890445 | 1(Win) | true |
| Jsonifier | 2198.2 | 0.115359 | 797.243ms | 18245 | 4890 | 407727 | 7915.48 | 0.244185 | 1.12212 | 2(Loss) | true |
| simdjson (ondemand) | 1821.3 | 0.106667 | 960.854ms | 18245 | 4890 | 507801 | 9553.5 | 0.0269227 | 1.35531 | 3(Loss) | true |
| Glaze | 1701.33 | 0.317843 | 1025.8ms | 18245 | 4890 | 5.1671e+06 | 10227.2 | 0.00138415 | 1.45121 | 4(Loss) | true |
