
----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 10189 | 0.174498 | 9876.84ms | 16197085 | 320 | 2.23944e+09 | 1.51602e+06 | 0.471015 | 1(Win) | true |
| simdjson (ondemand) | 8293.35 | 0.0956118 | 5973.29ms | 16197085 | 30 | 9.51388e+07 | 1.86255e+06 | 1.48583 | 2(Loss) | true |
