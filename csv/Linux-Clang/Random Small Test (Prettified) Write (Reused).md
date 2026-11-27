
----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16467.3 | 0.118947 | 783.928ms | 9255 | 4890 | 1987.57 | 535.988 | 0.124565 | 0.330594 | 1.44009 | 0.247758 | 0.000216762 | 2.13006e-05 | 4.88323e-06 | 1(Win) | true |
| Glaze | 3844.08 | 0.119149 | 961.827ms | 9255 | 4890 | 36597.7 | 2296.06 | 0.161957 | 1.34133 | 4.61632 | 0.778498 | 0.000228142 | 2.99402e-05 | 1.00758e-05 | 2(Loss) | true |
