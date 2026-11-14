
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 728.126 | 0.379097 | 9309.33ms | 4203058 | 30 | 1.3066e+10 | 5.50502e+06 | 0.281368 | 1(Win) | true |
| simdjson (ondemand) | 570.092 | 0.915741 | 5238.54ms | 4203058 | 40 | 1.65824e+11 | 7.03106e+06 | 3.57563 | 2(Loss) | true |
