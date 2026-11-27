
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2403.43 | 0.278042 | 779.209ms | 1313 | 1280 | 2685.93 | 520.994 | 0.0792384 | 2.32148 | 12.3534 | 1.35263 | 0.000840156 | 0.000117217 | 1.13052e-05 | 1(Win) | true |
| Glaze | 1076.52 | 0.117417 | 850.365ms | 1313 | 2560 | 4775.18 | 1163.17 | 0.0410887 | 4.96183 | 21.3481 | 2.74334 | 0.00313482 | 0.000174338 | 5.32535e-05 | 2(Loss) | true |
