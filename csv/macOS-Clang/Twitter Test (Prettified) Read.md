
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2276.29 | 0.131827 | 6882.17ms | 631514 | 640 | 7.78581e+07 | 264579 | 0.0716143 | 1(Win) | true |
| Jsonifier (two-stage) | 2188.27 | 0.216719 | 7110.14ms | 631514 | 160 | 5.6922e+07 | 275221 | 0.208411 | 2(Loss) | true |
| Glaze | 1967.01 | 0.272988 | 7914.24ms | 631514 | 30 | 2.09585e+07 | 306179 | 0.412752 | 3(Loss) | true |
| simdjson (ondemand) | 1095.89 | 0.470812 | 7004.91ms | 631514 | 30 | 2.0084e+08 | 549563 | 0.15391 | 4(Loss) | true |
