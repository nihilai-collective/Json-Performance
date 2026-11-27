
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1040.19 | 0.126344 | 6345.27ms | 500299 | 320 | 1.07472e+08 | 458688 | 0.131798 | 1(Win) | true |
| simdjson (ondemand) | 912.326 | 0.098353 | 7161.79ms | 500299 | 640 | 1.69322e+08 | 522973 | 0.0211492 | 2(Loss) | true |
