
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19477.1 | 0.0850084 | 3086.9ms | 475954 | 4890 | 1.91917e+06 | 23304.5 | 0.00616214 | 0.259654 | 1.01992 | 0.152899 | 0.000287488 | 0.000879462 | 2.97841e-06 | 1(Win) | true |
| Glaze | 6219.99 | 0.348161 | 8093.8ms | 475954 | 640 | 4.13134e+07 | 72975.2 | 0.0699064 | 0.810974 | 2.36357 | 0.337163 | 0.000364991 | 0.0118293 | 2.31049e-05 | 2(Loss) | true |
