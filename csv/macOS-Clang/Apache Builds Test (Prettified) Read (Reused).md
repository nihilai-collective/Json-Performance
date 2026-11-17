
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2044.37 | 0.617965 | 7296.32ms | 124597 | 160 | 2.06416e+07 | 58122.9 | 0.0169977 | 1(Win) | true |
| Jsonifier (two-stage) | 1843.62 | 0.160701 | 8759.22ms | 124597 | 320 | 3.43288e+06 | 64451.8 | 0.00156127 | 2(Loss) | true |
| Glaze | 1739.82 | 0.135521 | 8446.56ms | 124597 | 320 | 2.74139e+06 | 68297.3 | 0.423164 | 3(Loss) | true |
| simdjson (ondemand) | 1396.7 | 0.0857123 | 5299.33ms | 124597 | 640 | 3.40309e+06 | 85075.3 | 0.148986 | 4(Loss) | true |
