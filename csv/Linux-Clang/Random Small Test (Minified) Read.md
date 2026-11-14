
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1238.75 | 0.0495591 | 1099.16ms | 4926 | 2560 | 9042.88 | 3792.36 | 0.174676 | 4.19804 | 17.1961 | 3.36785 | 0.00424026 | 4.34556e-05 | 1.20534e-05 | 1(Win) | true |
| simdjson (ondemand) | 1039.4 | 0.0298164 | 1175.26ms | 4926 | 4890 | 8880.64 | 4519.73 | 0.112225 | 4.99802 | 19.6762 | 3.44478 | 0.00541769 | 8.00394e-05 | 3.00148e-05 | 2(Loss) | true |
