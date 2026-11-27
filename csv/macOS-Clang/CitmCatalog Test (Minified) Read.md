
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2131.82 | 0.15864 | 5730.23ms | 500299 | 80 | 1.00849e+07 | 223810 | 0.0865935 | 1(Win) | true |
| Jsonifier (two-stage) | 1482.19 | 0.109952 | 8357.15ms | 500299 | 160 | 2.00437e+07 | 321904 | 0.0377273 | 2(Loss) | true |
| Glaze | 1274.52 | 0.191491 | 9771.05ms | 500299 | 80 | 4.11104e+07 | 374354 | 0.200875 | 3(Loss) | true |
| simdjson (ondemand) | 852.541 | 0.127878 | 7149.26ms | 500299 | 640 | 3.27792e+08 | 559647 | 0.0497771 | 4(Loss) | true |
