
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2197.35 | 0.222492 | 755.126ms | 905 | 4890 | 3734.54 | 392.78 | 0.0421326 | 2.58924 | 9.3105 | 0.950277 | 0.00348078 | 0.000192523 | 0.000123151 | 1(Win) | true |
| Glaze | 221.043 | 0.144062 | 1121.15ms | 905 | 80 | 2531.24 | 3904.55 | 0.10809 | 23.5519 | 112.617 | 22.8608 | 0.0787155 | 8.28729e-05 | 0 | 2(Loss) | true |
