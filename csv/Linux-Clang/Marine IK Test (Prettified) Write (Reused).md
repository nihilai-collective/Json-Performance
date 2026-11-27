
----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4833.38 | 0.0665793 | 6203.11ms | 10018896 | 160 | 2.77164e+08 | 1.97683e+06 | 0.0999167 | 1.05489 | 3.43758 | 0.404007 | 0.00023495 | 0.02464 | 0.000353631 | 1(Win) | true |
| Glaze | 4091.43 | 0.0865354 | 7202.56ms | 9930228 | 80 | 3.20957e+08 | 2.31465e+06 | 0.0524724 | 1.23525 | 4.21632 | 0.484654 | 0.00111033 | 0.0220355 | 0.000609454 | 2(Loss) | true |
