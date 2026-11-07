
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3023.33 | 0.130049 | 2095.02ms | 56369 | 2560 | 1.36886e+06 | 17780.9 | 0.0649458 | 0.817695 | 1(Win) | true |
| Jsonifier (two-stage) | 2356.61 | 0.144361 | 2606.48ms | 56369 | 640 | 694044 | 22811.4 | 0.0715822 | 1.04936 | 2(Loss) | true |
| Glaze | 2069.82 | 0.0806805 | 2928.85ms | 56369 | 2560 | 1.12406e+06 | 25972.1 | 0.141706 | 1.19497 | 3(Loss) | true |
| simdjson (ondemand) | 994.039 | 0.0518306 | 5753.96ms | 56369 | 2560 | 2.01134e+06 | 54080 | 0.0501686 | 2.48934 | 4(Loss) | true |
