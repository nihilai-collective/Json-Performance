
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2520.97 | 0.328458 | 9476.32ms | 466906 | 320 | 1.07704e+08 | 176629 | 0.435814 | 1(Win) | true |
| Glaze | 1645.57 | 0.618429 | 7297.25ms | 466906 | 40 | 1.12012e+08 | 270591 | 1.0332 | 2(Loss) | true |
| simdjson (ondemand) | 1070.12 | 0.464843 | 5228.81ms | 466906 | 640 | 2.39436e+09 | 416101 | 1.29733 | 3(Loss) | true |
