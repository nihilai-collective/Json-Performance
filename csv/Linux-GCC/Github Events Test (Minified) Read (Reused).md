
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.56 | 0.0406321 | 4502.76ms | 53331 | 1280 | 221616 | 32383.7 | 0.0816922 | 3.26981 | 11.6734 | 2.21337 | 0.0103718 | 2.05234e-05 | 1.01958e-05 | 1(Win) | true |
| simdjson (ondemand) | 1233.94 | 0.0824095 | 5420.1ms | 53331 | 320 | 369210 | 41217.8 | 0.0287352 | 4.15354 | 15.6297 | 3.00451 | 0.0165201 | 1.67585e-05 | 6.67998e-06 | 2(Loss) | true |
