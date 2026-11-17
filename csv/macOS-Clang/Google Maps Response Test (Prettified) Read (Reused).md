
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2291.03 | 0.302786 | 1045.65ms | 25388 | 1280 | 1.31063e+06 | 10568.1 | 0.316087 | 1(Win) | true |
| Jsonifier (two-stage) | 1959.64 | 1.09061 | 1247.1ms | 25388 | 40 | 726278 | 12355.2 | 1.48638 | 2(Loss) | true |
| simdjson (ondemand) | 1627.3 | 0.0790901 | 1619.44ms | 25388 | 80 | 11077.9 | 14878.6 | 0.0596139 | 3(Loss) | true |
| Glaze | 1358.1 | 0.301148 | 1577.19ms | 25388 | 640 | 1.84474e+06 | 17827.8 | 0.327135 | 4(Loss) | true |
