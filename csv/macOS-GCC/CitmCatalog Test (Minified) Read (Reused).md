
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2609.23 | 0.150657 | 5832.72ms | 500299 | 160 | 1.21432e+07 | 182859 | 0.0113736 | 1(Win) | true |
| Jsonifier (two-stage) | 1393.67 | 0.421044 | 10272.2ms | 500299 | 320 | 6.64883e+08 | 342350 | 0.496686 | 2(Loss) | true |
| Glaze | 1317.12 | 0.540125 | 9462.78ms | 500299 | 320 | 1.22503e+09 | 362246 | 0.298571 | 3(Loss) | true |
| simdjson (reflection) | 1159.96 | 0.295266 | 5817.59ms | 500299 | 640 | 9.44012e+08 | 411325 | 0.0278048 | 4(Loss) | true |
| simdjson (ondemand) | 1094.25 | 0.601595 | 5993.07ms | 500299 | 160 | 1.10092e+09 | 436027 | 1.88923 | 5(Loss) | true |
