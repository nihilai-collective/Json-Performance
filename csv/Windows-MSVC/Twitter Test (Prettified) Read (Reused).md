
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1932.5 | 0.110625 | 8938.23ms | 631514 | 40 | 4.75435e+06 | 311648 | 0.119383 | 1.57264 | 1(Win) | true |
| Glaze | 1820.12 | 0.0343711 | 9382.54ms | 631514 | 640 | 8.27812e+06 | 330889 | 0.0344124 | 1.66976 | 2(Loss) | true |
| Jsonifier | 1785.25 | 0.0384407 | 9512.88ms | 631514 | 1280 | 2.15258e+07 | 337352 | 0.102279 | 1.70235 | 3(Loss) | true |
| simdjson (ondemand) | 1505.13 | 0.484408 | 5543.81ms | 631514 | 40 | 1.5028e+08 | 400138 | 0.226698 | 2.01924 | 4(Loss) | true |
