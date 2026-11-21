
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2319.77 | 0.119575 | 5459.56ms | 94653 | 640 | 1.3856e+06 | 38912.5 | 0.0203901 | 1(Win) | true |
| Jsonifier (two-stage) | 1503.22 | 0.181354 | 8454.86ms | 94653 | 320 | 3.79515e+06 | 60050 | 0.0303954 | 2(Loss) | true |
| Glaze | 1475.52 | 0.0619292 | 7653.14ms | 94653 | 2560 | 3.67461e+06 | 61177.2 | 0.0387479 | 3(Loss) | true |
| simdjson (ondemand) | 962.404 | 0.628194 | 5391.34ms | 94653 | 320 | 1.11094e+08 | 93794.4 | 0.341544 | 4(Loss) | true |
