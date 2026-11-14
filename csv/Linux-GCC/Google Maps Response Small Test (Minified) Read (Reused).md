
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2616.22 | 0.120054 | 902.068ms | 4390 | 1280 | 4724.4 | 1600.26 | 0.142024 | 2.01962 | 9.39385 | 1.44465 | 0.000944085 | 3.25669e-05 | 1.28132e-05 | 1(Win) | true |
| Glaze | 2163.23 | 0.0848668 | 934.352ms | 4390 | 4890 | 13191.9 | 1935.36 | 0.00242902 | 2.42327 | 11.6973 | 2.28428 | 0.000603575 | 3.47509e-05 | 1.2065e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1886.54 | 0.0550395 | 971.073ms | 4390 | 2560 | 3819.32 | 2219.21 | 0.0277154 | 2.78066 | 12.8804 | 1.98087 | 0.0031791 | 9.90354e-05 | 4.5736e-05 | 3(Loss) | true |
| simdjson (reflection) | 1602.64 | 0.0834319 | 1001.87ms | 4390 | 4890 | 23229 | 2612.33 | 0.0853404 | 3.25201 | 12.7442 | 1.97791 | 0.00253667 | 4.50457e-05 | 1.50463e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1214.28 | 0.101029 | 1091.74ms | 4390 | 30 | 364.006 | 3447.83 | 0.0793397 | 4.29399 | 16.4374 | 2.87403 | 0.00309795 | 8.35232e-05 | 0 | 5(Loss) | true |
