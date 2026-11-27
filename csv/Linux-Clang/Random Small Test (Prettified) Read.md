
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.86 | 0.0339062 | 1151.95ms | 8150 | 4890 | 9924.4 | 4201.64 | 0.0357102 | 2.80205 | 10.9156 | 1.97976 | 0.00515957 | 5.52775e-05 | 2.36868e-05 | 1(Win) | true |
| simdjson (ondemand) | 1568.15 | 0.0409162 | 1234.85ms | 8150 | 2560 | 10528.5 | 4956.43 | 0.0216134 | 3.296 | 12.3189 | 2.08466 | 0.00580967 | 5.67964e-05 | 2.64571e-05 | 2(Loss) | true |
