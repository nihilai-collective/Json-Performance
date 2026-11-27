
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1859.65 | 0.0531146 | 6514.09ms | 94653 | 30 | 19941.3 | 48540.3 | 0.0599828 | 1(Win) | true |
| Jsonifier (two-stage) | 1623.78 | 0.0793829 | 7251.85ms | 94653 | 1280 | 2.49275e+06 | 55591.4 | 0.0414819 | 2(Loss) | true |
| Glaze | 1468.28 | 0.166218 | 7776.03ms | 94653 | 320 | 3.34164e+06 | 61478.9 | 0.357443 | 3(Loss) | true |
| simdjson (ondemand) | 1052.51 | 0.132377 | 5325.35ms | 94653 | 320 | 4.12472e+06 | 85765 | 0.0135126 | 4(Loss) | true |
