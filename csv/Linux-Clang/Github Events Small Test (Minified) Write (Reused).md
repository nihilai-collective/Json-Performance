
----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12873.2 | 0.400143 | 745.078ms | 1996 | 4890 | 1711.93 | 147.868 | 0.0411188 | 0.503967 | 1.38477 | 0.196894 | 0.000501309 | 4.30308e-05 | 7.88899e-06 | 1(Win) | true |
| Glaze | 4196.5 | 0.444683 | 768.138ms | 1996 | 640 | 2603.91 | 453.6 | 0.302214 | 1.3131 | 3.25601 | 0.480461 | 0.000501785 | 2.58329e-05 | 7.82816e-07 | 2(Loss) | true |
