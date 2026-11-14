
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.13 | 0.101002 | 8740.48ms | 409725 | 320 | 3.72246e+07 | 337683 | 0.0358582 | 2.13931 | 1(Win) | true |
| simdjson (ondemand) | 1116.82 | 0.128537 | 9037.02ms | 409725 | 80 | 1.61796e+07 | 349872 | 1.17029 | 2.21658 | 2(Loss) | true |
