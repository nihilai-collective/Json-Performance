
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5145.72 | 0.35185 | 9272.24ms | 466906 | 30 | 2.781e+06 | 86533.3 | 0.707745 | 1(Win) | true |
| Jsonifier (two-stage) | 4920.29 | 0.277256 | 9255.35ms | 466906 | 1280 | 8.05841e+07 | 90498 | 0.499221 | 2(Loss) | true |
| simdjson (ondemand) | 3771.06 | 0.232448 | 6260.92ms | 466906 | 1280 | 9.64262e+07 | 118077 | 1.22051 | 3(Loss) | true |
| Glaze | 2200.65 | 0.175885 | 5309.85ms | 466906 | 160 | 2.02645e+07 | 202339 | 0.00408642 | 4(Loss) | true |
