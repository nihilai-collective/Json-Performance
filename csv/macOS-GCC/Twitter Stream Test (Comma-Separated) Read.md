
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1431.32 | 0.566427 | 9543.31ms | 4219119 | 30 | 7.60639e+09 | 2.81115e+06 | 0.213549 | 1(Win) | true |
| simdjson (ondemand) | 1200.29 | 0.748127 | 5677.69ms | 4219119 | 30 | 1.88686e+10 | 3.35223e+06 | 0.420786 | 2(Loss) | true |
