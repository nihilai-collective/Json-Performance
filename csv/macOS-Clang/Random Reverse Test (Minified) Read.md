
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 669.636 | 0.265077 | 7448.87ms | 409725 | 320 | 7.656e+08 | 583517 | 0.318502 | 1(Win) | true |
| simdjson (ondemand) | 313.263 | 0.200516 | 7910.42ms | 409725 | 320 | 2.00178e+09 | 1.24733e+06 | 0.394154 | 2(Loss) | true |
