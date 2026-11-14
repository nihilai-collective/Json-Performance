
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3827.07 | 0.0242558 | 3625.7ms | 108313 | 2560 | 109723 | 26990.7 | 5.49958e-05 | 1.31979 | 6.65907 | 1.33399 | 0.00193041 | 7.51944e-06 | 4.42872e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2509.8 | 0.020175 | 5040.91ms | 108313 | 4890 | 337148 | 41156.8 | 0.0950973 | 2.01269 | 9.56858 | 1.66868 | 0.00255955 | 1.7049e-05 | 1.23685e-05 | 2(Loss) | true |
| Glaze | 2485.62 | 0.0462291 | 5076.99ms | 108313 | 1280 | 472424 | 41557.1 | 0.0533079 | 2.03362 | 9.37268 | 1.76545 | 0.00276017 | 2.3478e-05 | 1.68565e-05 | 3(Loss) | true |
| simdjson (reflection) | 1718.86 | 0.0244119 | 6938.82ms | 108313 | 2560 | 550968 | 60095.3 | 0.142297 | 2.93031 | 12.7902 | 1.96247 | 0.0025147 | 2.3377e-05 | 1.63913e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1552.15 | 0.0627597 | 7623.3ms | 108313 | 80 | 139555 | 66549.8 | 0.145431 | 3.25657 | 14.2468 | 2.49171 | 0.00289774 | 4.03922e-06 | 1.38488e-06 | 5(Loss) | true |
