
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25871 | 0.0597052 | 1531.24ms | 213963 | 640 | 14192.4 | 7887.25 | 0.0305186 | 0.196252 | 0.6379 | 0.0747139 | 2.97949e-05 | 1.3656e-06 | 6.20726e-07 | 1(Win) | true |
| Glaze | 6298.38 | 0.166419 | 3978.78ms | 213963 | 640 | 1.86039e+06 | 32397.4 | 0.0165206 | 0.800743 | 3.56743 | 0.569169 | 0.000528377 | 4.20633e-06 | 2.4537e-06 | 2(Loss) | true |
| simdjson (reflection) | 486.751 | 0.244325 | 5475.15ms | 213963 | 640 | 6.71399e+08 | 419210 | 0.154773 | 10.4301 | 41.6031 | 8.43754 | 0.0391298 | 0.208923 | 0.000614023 | 3(Loss) | true |
