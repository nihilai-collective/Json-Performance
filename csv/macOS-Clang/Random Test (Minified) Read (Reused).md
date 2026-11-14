
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1744.99 | 0.0869162 | 8477.98ms | 461466 | 1280 | 6.15043e+07 | 252201 | 0.018895 | 1(Win) | true |
| Jsonifier (two-stage) | 1343.14 | 0.228179 | 5545.32ms | 461466 | 160 | 8.9435e+07 | 327655 | 0.0500032 | 2(Loss) | true |
| Glaze | 1045.75 | 0.259165 | 6362.96ms | 461466 | 80 | 9.51636e+07 | 420837 | 0.037726 | 3(Loss) | true |
| simdjson (ondemand) | 749.384 | 0.154341 | 8372.13ms | 461466 | 640 | 5.25788e+08 | 587267 | 0.0720214 | 4(Loss) | true |
