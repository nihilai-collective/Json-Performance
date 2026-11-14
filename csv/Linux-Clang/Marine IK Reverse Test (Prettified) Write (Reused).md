
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4913.7 | 0.440564 | 6033.05ms | 9930848 | 160 | 1.1537e+10 | 1.92743e+06 | 0.258786 | 1.02269 | 3.38766 | 0.427905 | 0.000531428 | 0.0246217 | 0.000207886 | 1(Win) | true |
| Glaze | 3997.63 | 0.431942 | 7433.49ms | 9930228 | 80 | 8.37632e+09 | 2.36895e+06 | 0.165073 | 1.2661 | 4.21647 | 0.484654 | 0.0010538 | 0.0220311 | 0.000231878 | 2(Loss) | true |
