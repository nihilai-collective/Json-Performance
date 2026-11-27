
----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 545.68 | 0.083451 | 9747.47ms | 108313 | 1280 | 3.19418e+07 | 189297 | 0.00872191 | 1(Win) | true |
| simdjson (ondemand) | 160.073 | 0.126747 | 8192.65ms | 108313 | 640 | 4.28135e+08 | 645302 | 0.292964 | 2(Loss) | true |
