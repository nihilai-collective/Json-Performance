
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2173.96 | 0.954785 | 6093.84ms | 500299 | 80 | 3.51283e+08 | 219471 | 1.9084 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.23 | 0.163539 | 8750.34ms | 500299 | 160 | 3.857e+07 | 300223 | 0.223144 | 2(Loss) | true |
| Glaze | 1421.47 | 0.17079 | 9903.08ms | 500299 | 80 | 2.62904e+07 | 335655 | 0.105446 | 3(Loss) | true |
| simdjson (ondemand) | 868.236 | 0.0963015 | 7369.09ms | 500299 | 640 | 1.79238e+08 | 549531 | 0.26402 | 4(Loss) | true |
