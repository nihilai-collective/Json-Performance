
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 518.774 | 1.00125 | 5309.42ms | 4203058 | 40 | 2.39399e+11 | 7.72657e+06 | 0.605187 | 1(Win) | true |
| simdjson (ondemand) | 435.219 | 0.876356 | 6498.14ms | 4203058 | 40 | 2.60577e+11 | 9.20997e+06 | 1.43868 | 2(Loss) | true |
