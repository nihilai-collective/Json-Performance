
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2347.93 | 0.0515346 | 1552.65ms | 18245 | 640 | 9334.61 | 7410.71 | 0.083235 | 2.20511 | 9.15314 | 1.69164 | 0.00240811 | 1.19039e-05 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 2251.19 | 0.0254098 | 1579.27ms | 18245 | 2560 | 9874.35 | 7729.16 | 0.0592366 | 2.29943 | 9.50441 | 1.54409 | 0.00243705 | 1.24178e-05 | 9.63449e-07 | 2(Loss) | true |
