
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 670.793 | 0.221291 | 8308.36ms | 1834197 | 30 | 9.98999e+08 | 2.6077e+06 | 0.194429 | 3.69081 | 1(Win) | true |
| Jsonifier (two-stage) | 613.668 | 0.488185 | 8877.87ms | 1834197 | 80 | 1.54911e+10 | 2.85044e+06 | 0.339871 | 4.03435 | 2(Loss) | true |
| simdjson (ondemand) | 219.451 | 0.605732 | 5656.91ms | 1834197 | 30 | 6.99355e+10 | 7.9709e+06 | 0.421884 | 11.2818 | 3(Loss) | true |
| Glaze | 205.811 | 0.717272 | 5961.15ms | 1834197 | 30 | 1.11492e+11 | 8.49918e+06 | 1.60944 | 12.0291 | 4(Loss) | true |
