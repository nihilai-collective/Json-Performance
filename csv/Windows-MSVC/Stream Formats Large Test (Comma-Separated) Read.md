
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 15740.8 | 0.161666 | 6211.58ms | 16197085 | 160 | 4.02694e+08 | 981316 | 0.231346 | 0.193014 | 1(Win) | true |
| simdjson (ondemand) | 13671.9 | 0.446901 | 7266.33ms | 16197085 | 160 | 4.07903e+09 | 1.12981e+06 | 0.305145 | 0.222223 | 2(Loss) | true |
