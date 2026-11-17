
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1824.56 | 0.0329378 | 7261.09ms | 124597 | 640 | 294489 | 65125.4 | 0.139823 | 2.77243 | 11.8363 | 2.25794 | 0.00720332 | 4.0631e-06 | 1.3042e-06 | 1(Win) | true |
| simdjson (ondemand) | 1572.38 | 0.0643845 | 8218.88ms | 124597 | 80 | 189389 | 75570.2 | 0.00868473 | 3.21559 | 12.931 | 2.3761 | 0.0103689 | 3.31067e-06 | 9.02911e-07 | 2(Loss) | true |
