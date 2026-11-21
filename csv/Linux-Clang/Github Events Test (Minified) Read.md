
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1818.56 | 0.0813741 | 2838.36ms | 53331 | 2560 | 1.32592e+06 | 27967.4 | 0.0989868 | 1.36013 | 1(Win) | true |
| Jsonifier | 1696.59 | 0.104286 | 3088.67ms | 53331 | 2560 | 2.50205e+06 | 29977.9 | 1.04917 | 1.45796 | 2(Loss) | true |
| Glaze | 1411.04 | 0.128588 | 3526.61ms | 53331 | 2560 | 5.49949e+06 | 36044.7 | 0.320356 | 1.7533 | 3(Loss) | true |
| simdjson (ondemand) | 988.472 | 0.0713447 | 5135.63ms | 53331 | 4890 | 6.58966e+06 | 51453.6 | 1.12763 | 2.50325 | 4(Loss) | true |
