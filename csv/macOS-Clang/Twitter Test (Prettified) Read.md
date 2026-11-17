
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 2047.19 | 0.838435 | 8287.09ms | 631514 | 40 | 2.43359e+08 | 294187 | 5.71418 | -(Win) | false |
| Jsonifier | 1838.2 | 0.426605 | 8300.2ms | 631514 | 1280 | 2.5006e+09 | 327636 | 1.18282 | 2(Loss) | true |
| Glaze | 1608.16 | 0.843907 | 9637.29ms | 631514 | 80 | 7.99077e+08 | 374503 | 3.66102 | 3(Loss) | true |
| simdjson (ondemand) | 954.585 | 0.581263 | 8359.12ms | 631514 | 320 | 4.30361e+09 | 630912 | 0.477479 | 4(Loss) | true |
