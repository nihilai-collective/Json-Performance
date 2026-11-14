
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5300.22 | 0.083435 | 1182.99ms | 24579 | 4890 | 66580.4 | 4422.53 | 0.267308 | 0.964288 | 2.95268 | 0.383987 | 0.000125625 | 2.35208e-05 | 1.0658e-05 | 1(Win) | true |
| Glaze | 3989.47 | 0.121402 | 1331.74ms | 24579 | 2560 | 130254 | 5875.56 | 0.0203463 | 1.27911 | 3.59408 | 0.447374 | 0.00029716 | 9.63093e-06 | 2.95603e-06 | 2(Loss) | true |
