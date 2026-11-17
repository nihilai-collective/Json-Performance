
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1499.17 | 1.23818 | 5243.09ms | 631514 | 80 | 1.97935e+09 | 401729 | 2.28743 | 1.65128 | 1(Win) | true |
| Jsonifier | 1279.7 | 0.383016 | 6141.57ms | 631514 | 40 | 1.2997e+08 | 470625 | 0.142922 | 1.93451 | 2(Loss) | true |
| Glaze | 1255.08 | 0.594327 | 6166.19ms | 631514 | 160 | 1.30134e+09 | 479855 | 0.384052 | 1.97239 | 3(Loss) | true |
| simdjson (ondemand) | 1162.95 | 0.372717 | 6805.53ms | 631514 | 40 | 1.49025e+08 | 517870 | 0.135352 | 2.12872 | 4(Loss) | true |
