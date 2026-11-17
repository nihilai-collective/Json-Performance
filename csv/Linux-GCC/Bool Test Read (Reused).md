
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 523.302 | 0.081691 | 877.187ms | 905 | 2560 | 4647.08 | 1649.29 | 0.0695367 | 10.0231 | 54.8055 | 5.27735 | 0.0015379 | 0.000110497 | 2.28764e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.311 | 0.048749 | 1092.4ms | 905 | 2560 | 8693.91 | 3780.26 | 0.124464 | 22.7593 | 103.737 | 9.68509 | 0.0889654 | 0.000200708 | 6.34496e-05 | 2(Loss) | true |
