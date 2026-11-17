
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5475.54 | 0.101569 | 1169.47ms | 24579 | 4890 | 92450.4 | 4280.92 | 0.102826 | 0.931229 | 2.95594 | 0.383946 | 0.000126174 | 1.30126e-05 | 4.2682e-06 | 1(Win) | true |
| Glaze | 3881.49 | 0.0882327 | 1352.48ms | 24579 | 4890 | 138835 | 6039.02 | 0.154343 | 1.31059 | 3.59514 | 0.447659 | 0.000235258 | 9.58472e-06 | 2.51266e-06 | 2(Loss) | true |
