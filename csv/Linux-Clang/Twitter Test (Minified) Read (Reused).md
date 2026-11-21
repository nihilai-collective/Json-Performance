
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2363.84 | 0.0825528 | 5640.52ms | 466906 | 640 | 1.54762e+07 | 188370 | 0.135389 | 1.04716 | 1(Win) | true |
| Jsonifier | 2171.53 | 0.220613 | 6030.61ms | 466906 | 80 | 1.63712e+07 | 205052 | 0.115024 | 1.13989 | 2(Loss) | true |
| Glaze | 2071.48 | 0.250395 | 6238.28ms | 466906 | 30 | 8.69102e+06 | 214956 | 0.220581 | 1.19504 | 3(Loss) | true |
| simdjson (ondemand) | 1036.57 | 0.205376 | 5908.17ms | 466906 | 30 | 2.335e+07 | 429569 | 0.0253213 | 2.38827 | 4(Loss) | true |
