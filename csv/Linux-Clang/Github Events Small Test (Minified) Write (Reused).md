
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11973.8 | 0.428643 | 750.197ms | 1996 | 4890 | 2270.68 | 158.975 | 0.234577 | 0.534167 | 1.35671 | 0.20992 | 0.000501617 | 4.07769e-05 | 6.55708e-06 | 1(Win) | true |
| Glaze | 3894.42 | 0.351577 | 781.066ms | 1996 | 1280 | 3779.96 | 488.785 | 0.0878265 | 1.40757 | 3.25601 | 0.480462 | 0.000507656 | 3.91408e-05 | 1.17422e-06 | 2(Loss) | true |
