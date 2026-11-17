
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1757.54 | 0.291714 | 7571.89ms | 94653 | 2560 | 5.74665e+07 | 51360.6 | 0.152802 | 1(Win) | true |
| Glaze | 1384.37 | 0.212172 | 8823.22ms | 94653 | 4890 | 9.35951e+07 | 65205.3 | 0.300379 | 2(Loss) | true |
| Jsonifier (two-stage) | 1150.54 | 0.400204 | 5032.9ms | 94653 | 1280 | 1.26195e+08 | 78457.4 | 0.155485 | 3(Loss) | true |
| simdjson (reflection) | 979.436 | 0.426579 | 5865.94ms | 94653 | 1280 | 1.97846e+08 | 92163.4 | 0.129285 | 4(Loss) | true |
| simdjson (ondemand) | 757.507 | 0.96138 | 7031.74ms | 94653 | 160 | 2.09994e+08 | 119165 | 2.80576 | 5(Loss) | true |
