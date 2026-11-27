
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 781.916 | 0.133586 | 7882.07ms | 4203058 | 30 | 1.40688e+09 | 5.12632e+06 | 0.445936 | 1(Win) | true |
| simdjson (ondemand) | 681.063 | 0.294007 | 9023.98ms | 4203058 | 30 | 8.98243e+09 | 5.88543e+06 | 0.268449 | 2(Loss) | true |
