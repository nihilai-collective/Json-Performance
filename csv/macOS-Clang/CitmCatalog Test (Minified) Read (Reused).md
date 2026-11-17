
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2446.45 | 0.464777 | 6102.85ms | 500299 | 30 | 2.46488e+07 | 195026 | 0.961391 | 1(Win) | true |
| Jsonifier (two-stage) | 1592.3 | 0.373242 | 9137.96ms | 500299 | 30 | 3.75242e+07 | 299643 | 1.18397 | 2(Loss) | true |
| Glaze | 1343.43 | 0.252607 | 5051.75ms | 500299 | 80 | 6.43892e+07 | 355153 | 0.0468909 | 3(Loss) | true |
| simdjson (ondemand) | 861.007 | 0.43509 | 7739.72ms | 500299 | 30 | 1.74392e+08 | 554144 | 0.3991 | 4(Loss) | true |
