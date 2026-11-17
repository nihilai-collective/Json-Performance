
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1274.94 | 1.24105 | 8901.11ms | 466906 | 160 | 3.00593e+09 | 349252 | 0.171014 | 1.94161 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.82 | 0.967101 | 5097.12ms | 466906 | 160 | 2.39594e+09 | 400135 | 0.197824 | 2.22452 | 2(Loss) | true |
| Glaze | 1069.88 | 0.739742 | 5380.14ms | 466906 | 160 | 1.5166e+09 | 416194 | 0.326331 | 2.31382 | 3(Loss) | true |
| simdjson (ondemand) | 875.314 | 0.596815 | 6417.44ms | 466906 | 640 | 5.89915e+09 | 508704 | 1.00566 | 2.82814 | 4(Loss) | true |
