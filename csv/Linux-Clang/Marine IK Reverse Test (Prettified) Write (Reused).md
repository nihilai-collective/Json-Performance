
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5051.15 | 0.129776 | 5848.78ms | 9930848 | 30 | 1.77624e+08 | 1.87498e+06 | 0.126934 | 1.00088 | 3.39345 | 0.427905 | 0.000360691 | 0.0247207 | 0.00130519 | 1(Win) | true |
| Glaze | 3990.94 | 0.17148 | 7391.26ms | 9930228 | 30 | 4.96724e+08 | 2.37292e+06 | 0.000240211 | 1.26143 | 4.21647 | 0.484654 | 0.00106339 | 0.0220178 | 0.000345162 | 2(Loss) | true |
