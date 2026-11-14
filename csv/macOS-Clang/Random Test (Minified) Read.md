
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1294.06 | 0.131689 | 8768.03ms | 461466 | 320 | 6.4183e+07 | 340084 | 0.128599 | 1(Win) | true |
| Jsonifier (two-stage) | 989.225 | 0.138046 | 5674.25ms | 461466 | 160 | 6.03471e+07 | 444882 | 0.37546 | 2(Loss) | true |
| Glaze | 865.257 | 0.166603 | 6474.94ms | 461466 | 320 | 2.29776e+08 | 508622 | 0.0378599 | 3(Loss) | true |
| simdjson (ondemand) | 658.279 | 0.132835 | 8566.41ms | 461466 | 320 | 2.52367e+08 | 668544 | 0.0268842 | 4(Loss) | true |
