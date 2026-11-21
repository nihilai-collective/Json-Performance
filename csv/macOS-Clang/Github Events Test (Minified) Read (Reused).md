
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2572.76 | 0.0806849 | 2529.54ms | 53331 | 2560 | 651305 | 19768.8 | 0.066532 | 1(Win) | true |
| Jsonifier (two-stage) | 2078.51 | 0.0417508 | 3041.32ms | 53331 | 40 | 4174.89 | 24469.7 | 0.00698192 | 2(Loss) | true |
| Glaze | 1974.56 | 0.200125 | 3092.96ms | 53331 | 160 | 425149 | 25757.8 | 0.00177127 | 3(Loss) | true |
| simdjson (ondemand) | 1016.94 | 0.136345 | 5502.76ms | 53331 | 1280 | 5.95197e+06 | 50013.3 | 0.152296 | 4(Loss) | true |
