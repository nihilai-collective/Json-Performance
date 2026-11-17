
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5034.67 | 0.143134 | 5865.6ms | 9930848 | 40 | 2.89985e+08 | 1.88112e+06 | 0.0373495 | 1.0006 | 3.40482 | 0.427905 | 0.000499655 | 0.0247206 | 0.00178387 | 1(Win) | true |
| Glaze | 4033.05 | 0.0927759 | 7289.6ms | 9930228 | 160 | 7.59352e+08 | 2.34815e+06 | 0.0551135 | 1.25085 | 4.21632 | 0.484654 | 0.00103996 | 0.0220181 | 0.00170947 | 2(Loss) | true |
