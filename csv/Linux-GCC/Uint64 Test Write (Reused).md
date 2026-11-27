
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3157.98 | 0.220124 | 776.936ms | 1213 | 80 | 52.015 | 366.312 | 0.146948 | 1.77997 | 8.39736 | 1.11789 | 0.000824402 | 6.18302e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3035 | 0.0318297 | 780.693ms | 1213 | 4890 | 71.9743 | 381.156 | 0.0163383 | 1.853 | 8.70074 | 1.11789 | 0.000824402 | 0.000117675 | 4.99025e-05 | 2(Loss) | true |
| Glaze | 953.622 | 0.0673793 | 861.715ms | 1213 | 2560 | 1710.26 | 1213.07 | 0.165144 | 5.48004 | 19.723 | 2.73207 | 0.000856283 | 0.000129457 | 2.86609e-05 | 3(Loss) | true |
