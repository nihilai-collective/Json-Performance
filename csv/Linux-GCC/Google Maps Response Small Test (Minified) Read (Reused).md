
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1527.21 | 0.0525157 | 1016.48ms | 4390 | 2560 | 5305.78 | 2741.36 | 0.0128403 | 3.42154 | 16.2075 | 2.97062 | 0.00139308 | 0.000120035 | 4.29776e-05 | 1(Win) | true |
| simdjson (ondemand) | 1184.94 | 0.0818291 | 1091.03ms | 4390 | 80 | 668.711 | 3533.19 | 0.00176897 | 4.39801 | 18.123 | 3.29499 | 0.00245159 | 7.97267e-05 | 2.84738e-06 | 2(Loss) | true |
