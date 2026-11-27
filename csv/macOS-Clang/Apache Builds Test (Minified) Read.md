
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1331.58 | 0.167359 | 6866.49ms | 94653 | 320 | 4.11887e+06 | 67790 | 0.0681651 | 1(Win) | true |
| Jsonifier (two-stage) | 1218.37 | 0.0984264 | 7569.9ms | 94653 | 640 | 3.40341e+06 | 74089.4 | 0.0940524 | 2(Loss) | true |
| Glaze | 1118.63 | 0.0550446 | 8218.48ms | 94653 | 2560 | 5.05089e+06 | 80695.5 | 0.165356 | 3(Loss) | true |
| simdjson (ondemand) | 833.87 | 0.391322 | 5322.94ms | 94653 | 40 | 7.17795e+06 | 108252 | 0.515114 | 4(Loss) | true |
