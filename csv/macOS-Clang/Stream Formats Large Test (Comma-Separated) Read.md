
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 8493.89 | 0.116314 | 5701.38ms | 16197085 | 40 | 1.78972e+08 | 1.81857e+06 | 0.0220083 | 1(Win) | true |
| Jsonifier (generic) | 7159.02 | 0.80963 | 6369.75ms | 16197085 | 40 | 1.22068e+10 | 2.15766e+06 | 0.71769 | 2(Loss) | true |
