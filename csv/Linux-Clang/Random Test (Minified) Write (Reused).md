
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14774.1 | 0.330342 | 3781.27ms | 461466 | 30 | 290489 | 29787.9 | 0.046909 | 0.343589 | 1.61236 | 0.263785 | 0.000521454 | 0.00765849 | 4.0523e-05 | 1(Win) | true |
| Glaze | 3923.14 | 0.345362 | 6165.13ms | 461466 | 640 | 9.60595e+07 | 112177 | 0.187174 | 1.27436 | 5.35474 | 0.788156 | 0.00998161 | 0.00877836 | 3.91145e-05 | 2(Loss) | true |
