
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 804.548 | 0.128456 | 7604.14ms | 4197495 | 80 | 3.26795e+09 | 4.97552e+06 | 0.0349664 | 1(Win) | true |
| simdjson (ondemand) | 461.271 | 0.10247 | 6130.16ms | 4197495 | 40 | 3.16314e+09 | 8.67828e+06 | 0.00985159 | 2(Loss) | true |
