
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2608.75 | 0.173473 | 5626.44ms | 500299 | 160 | 1.61057e+07 | 182893 | 0.232221 | 1(Win) | true |
| Jsonifier (two-stage) | 1706.06 | 0.0509652 | 8179.99ms | 500299 | 1280 | 2.60032e+07 | 279663 | 0.0440006 | 2(Loss) | true |
| Glaze | 1426.36 | 0.158477 | 9539.87ms | 500299 | 80 | 2.24813e+07 | 334503 | 0.0227002 | 3(Loss) | true |
| simdjson (ondemand) | 916.5 | 0.050291 | 7145.55ms | 500299 | 640 | 4.38688e+07 | 520592 | 0.0599422 | 4(Loss) | true |
