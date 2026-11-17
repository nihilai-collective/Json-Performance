
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1159.49 | 0.109393 | 9524.62ms | 1834197 | 40 | 1.08942e+08 | 1.50862e+06 | 0.0650845 | 4.34436 | 12.5609 | 0.909504 | 0.00117149 | 0.0602953 | 0.00105599 | 1(Win) | true |
| Glaze | 657.829 | 0.116442 | 8267.48ms | 1833577 | 80 | 7.66441e+08 | 2.65819e+06 | 0.121609 | 7.68291 | 16.0106 | 0.996384 | 0.00126873 | 0.0492953 | 0.000509387 | 2(Loss) | true |
