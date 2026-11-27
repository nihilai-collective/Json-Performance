
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1209.87 | 0.217462 | 9457.15ms | 94653 | 640 | 1.68475e+07 | 74609.7 | 0.344774 | 2.04555 | 1(Win) | true |
| simdjson (ondemand) | 1115.63 | 0.552005 | 5229.14ms | 94653 | 80 | 1.59591e+07 | 80912.5 | 0.297499 | 2.21839 | 2(Loss) | true |
| Glaze | 1082.4 | 0.153552 | 5366.71ms | 94653 | 1280 | 2.09903e+07 | 83396.5 | 0.174407 | 2.28658 | 3(Loss) | true |
| Jsonifier (two-stage) | 1056.79 | 0.738431 | 5507.35ms | 94653 | 40 | 1.59138e+07 | 85417.5 | 0.0829948 | 2.34178 | 4(Loss) | true |
