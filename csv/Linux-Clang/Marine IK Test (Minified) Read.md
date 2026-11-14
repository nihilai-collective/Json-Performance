
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8769.42 | 0.0469552 | 5304.31ms | 1834197 | 1280 | 1.12286e+07 | 199469 | 0.224468 | 0.580963 | 2.90983 | 0.136897 | 0.00243167 | 0.0377043 | 3.16726e-06 | 1(Win) | true |
| simdjson (stage-1) | 6950.3 | 0.062105 | 6639.29ms | 1834197 | 1280 | 3.12714e+07 | 251676 | 0.163301 | 0.737297 | 3.04774 | 0.152978 | 0.00462363 | 0.0376875 | 2.40526e-06 | 2(Loss) | true |
