
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5376.62 | 0.142588 | 1179.45ms | 24579 | 2560 | 98926.7 | 4359.68 | 0.0292717 | 0.949261 | 2.95134 | 0.383987 | 0.000125965 | 2.24086e-05 | 1.01872e-05 | 1(Win) | true |
| Glaze | 3636.08 | 0.112084 | 1394.05ms | 24579 | 2560 | 133655 | 6446.59 | 0.500732 | 1.41734 | 3.59408 | 0.447374 | 0.000408774 | 3.61716e-05 | 2.0136e-05 | 2(Loss) | true |
