
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21902.3 | 0.249953 | 4649.93ms | 837491 | 40 | 332323 | 36466.2 | 0.540511 | 0.235057 | 0.834832 | 0.124744 | 0.00013236 | 0.00397207 | 1.42688e-05 | 1(Win) | true |
| Glaze | 5529.1 | 0.638922 | 7827.81ms | 837491 | 2560 | 2.18066e+09 | 144453 | 0.091264 | 0.913284 | 4.42726 | 0.728068 | 0.00588083 | 0.010057 | 6.41686e-05 | 2(Loss) | true |
| simdjson (reflection) | 518.099 | 1.89267 | 9747.25ms | 837491 | 80 | 6.81041e+10 | 1.54159e+06 | 0.986328 | 9.8251 | 37.0578 | 7.06715 | 0.0248138 | 0.323419 | 0.00157463 | 3(Loss) | true |
