
----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 530.979 | 0.237952 | 9883.76ms | 108313 | 80 | 1.71425e+07 | 194538 | 0.0180909 | 1(Win) | true |
| simdjson (ondemand) | 216.904 | 0.0917519 | 6142.83ms | 108313 | 320 | 6.1095e+07 | 476226 | 0.0466788 | 2(Loss) | true |
