
----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14511.3 | 0.223822 | 6313.04ms | 837491 | 40 | 607031 | 55039.3 | 0.0679673 | 0.349971 | 1.40008 | 0.242085 | 0.000469318 | 0.0160659 | 1.81494e-05 | 1(Win) | true |
| Glaze | 4440.62 | 0.0684618 | 9602.25ms | 837491 | 2560 | 3.88159e+07 | 179861 | 0.0404036 | 1.1352 | 4.56028 | 0.768648 | 0.00620113 | 0.0170835 | 7.51202e-05 | 2(Loss) | true |
