
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5353.32 | 0.0777005 | 1181.54ms | 24579 | 4890 | 56602.9 | 4378.66 | 0.124875 | 0.952996 | 2.95264 | 0.383986 | 0.000183399 | 8.37831e-06 | 1.70561e-06 | 1(Win) | true |
| Glaze | 3994.89 | 0.0896262 | 1326.41ms | 24579 | 4890 | 135238 | 5867.58 | 0.243495 | 1.27456 | 3.59514 | 0.447659 | 0.000231115 | 7.70438e-06 | 8.65287e-07 | 2(Loss) | true |
