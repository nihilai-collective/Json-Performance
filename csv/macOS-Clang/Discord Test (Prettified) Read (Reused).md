
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2459.49 | 0.705302 | 3675.69ms | 83958 | 160 | 8.43537e+06 | 32554.9 | 2.45305 | 1(Win) | true |
| Glaze | 2001.09 | 0.806246 | 4505.94ms | 83958 | 30 | 3.12211e+06 | 40012.5 | 0.093892 | 2(Loss) | true |
| Jsonifier (two-stage) | 1910.95 | 0.734534 | 4886.49ms | 83958 | 320 | 3.0311e+07 | 41899.9 | 1.02149 | 3(Loss) | true |
| simdjson (ondemand) | 985.087 | 0.891566 | 7832.54ms | 83958 | 160 | 8.40238e+07 | 81280.7 | 0.391727 | 4(Loss) | true |
