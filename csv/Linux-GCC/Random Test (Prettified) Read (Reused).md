
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2476.35 | 0.148448 | 7972.54ms | 676745 | 1280 | 1.91596e+08 | 260624 | 0.185058 | 2.02714 | 9.75766 | 1.74775 | 0.00411636 | 0.0122346 | 4.26478e-05 | 1(Win) | true |
| simdjson (ondemand) | 1820.44 | 0.101016 | 5175.61ms | 676745 | 160 | 2.05209e+07 | 354526 | 0.0599557 | 2.79224 | 10.9298 | 1.92793 | 0.00840812 | 0.0193323 | 1.30958e-05 | 2(Loss) | true |
