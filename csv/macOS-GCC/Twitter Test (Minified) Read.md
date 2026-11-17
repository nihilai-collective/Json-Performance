
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.08 | 2.20021 | 6085.99ms | 466906 | 80 | 2.23368e+09 | 240160 | 0.308175 | 1(Win) | true |
| Jsonifier (two-stage) | 1713.26 | 0.427363 | 6881.64ms | 466906 | 30 | 3.70106e+07 | 259900 | 0.207278 | 2(Loss) | true |
| Glaze | 1436.28 | 0.267809 | 7992.37ms | 466906 | 1280 | 8.82354e+08 | 310021 | 1.41062 | 3(Loss) | true |
| simdjson (reflection) | 1153.35 | 0.641874 | 9494.73ms | 466906 | 30 | 1.8423e+08 | 386074 | 0.106206 | 4(Loss) | true |
| simdjson (ondemand) | 1042.02 | 0.173822 | 6277.96ms | 466906 | 40 | 2.20688e+07 | 427322 | 0.967547 | 5(Loss) | true |
