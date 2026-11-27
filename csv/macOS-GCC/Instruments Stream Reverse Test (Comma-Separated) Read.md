
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 760.34 | 0.347831 | 7948.78ms | 4197495 | 40 | 1.34141e+10 | 5.26481e+06 | 0.746656 | 1(Win) | true |
| simdjson (ondemand) | 499.611 | 0.260589 | 5675.37ms | 4197495 | 40 | 1.74376e+10 | 8.01231e+06 | 0.384905 | 2(Loss) | true |
