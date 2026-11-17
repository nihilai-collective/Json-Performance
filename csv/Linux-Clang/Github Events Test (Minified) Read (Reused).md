
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2194.31 | 0.192659 | 2842.82ms | 53331 | 1280 | 2.55242e+06 | 23178.3 | 0.598599 | 1.1269 | 1(Win) | true |
| Jsonifier | 2141.51 | 0.230046 | 3068.52ms | 53331 | 320 | 955210 | 23749.8 | 0.755582 | 1.15473 | 2(Loss) | true |
| Glaze | 1701.96 | 0.0952824 | 3584.62ms | 53331 | 2560 | 2.07551e+06 | 29883.4 | 0.320382 | 1.45329 | 3(Loss) | true |
| simdjson (ondemand) | 1064.15 | 0.129251 | 5430.61ms | 53331 | 1280 | 4.88462e+06 | 47794.2 | 0.196621 | 2.32507 | 4(Loss) | true |
