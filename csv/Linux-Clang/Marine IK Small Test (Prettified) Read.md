
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2097.61 | 0.0224212 | 1554.06ms | 18245 | 2560 | 8855.13 | 8295.05 | 0.00722905 | 2.46675 | 10.19 | 1.92706 | 0.00271232 | 1.43019e-05 | 3.57547e-06 | 1(Win) | true |
| simdjson (ondemand) | 1993.98 | 0.123651 | 1588.61ms | 18245 | 160 | 18627.8 | 8726.16 | 0.0491813 | 2.59344 | 10.5249 | 1.77632 | 0.0031101 | 2.98027e-05 | 1.50726e-05 | 2(Loss) | true |
