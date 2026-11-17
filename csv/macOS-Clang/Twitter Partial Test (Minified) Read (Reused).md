
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5100.87 | 0.0788378 | 9234.79ms | 466906 | 1280 | 6.06247e+06 | 87294.1 | 0.103593 | 1(Win) | true |
| Jsonifier (two-stage) | 4166.77 | 1.38052 | 5415.54ms | 466906 | 40 | 8.70574e+07 | 106864 | 1.00396 | 2(Loss) | true |
| simdjson (ondemand) | 3967.82 | 0.361636 | 6751.25ms | 466906 | 80 | 1.31761e+07 | 112222 | 0.393854 | 3(Loss) | true |
| Glaze | 2037.8 | 0.814206 | 5740.94ms | 466906 | 160 | 5.06434e+08 | 218508 | 0.614115 | 4(Loss) | true |
