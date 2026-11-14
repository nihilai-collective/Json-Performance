
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16908.6 | 0.183816 | 783.604ms | 9255 | 4890 | 4502.06 | 521.998 | 0.078829 | 0.323272 | 1.39751 | 0.264938 | 0.00027788 | 8.66165e-06 | 2.29799e-06 | 1(Win) | true |
| Glaze | 4610.3 | 0.177482 | 925.009ms | 9255 | 2560 | 29555.8 | 1914.47 | 0.0373048 | 1.11827 | 4.61632 | 0.778498 | 0.000384632 | 1.6925e-05 | 2.95448e-06 | 2(Loss) | true |
