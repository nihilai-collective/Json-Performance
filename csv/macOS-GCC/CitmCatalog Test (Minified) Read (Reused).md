
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.77 | 0.493415 | 6505.16ms | 500299 | 640 | 6.38602e+08 | 202448 | 1.35556 | 1(Win) | true |
| Jsonifier (two-stage) | 1339.77 | 1.8392 | 5069.66ms | 500299 | 80 | 3.43199e+09 | 356122 | 4.92268 | 2(Loss) | true |
| Glaze | 1268.32 | 1.01932 | 5037.38ms | 500299 | 30 | 4.41106e+08 | 376183 | 0.300328 | 3(Loss) | true |
| simdjson (reflection) | 1163.44 | 0.281749 | 5930.92ms | 500299 | 160 | 2.13607e+08 | 410096 | 0.445898 | 4(Loss) | true |
| simdjson (ondemand) | 1053.13 | 1.30782 | 6075.65ms | 500299 | 30 | 1.0532e+09 | 453052 | 0.0583551 | 5(Loss) | true |
