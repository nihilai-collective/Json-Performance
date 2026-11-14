
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2771.47 | 0.129636 | 3757.86ms | 108313 | 2560 | 5.97627e+06 | 37270.9 | 0.216054 | 1.09592 | 1(Win) | true |
| simdjson (ondemand) | 2131.91 | 0.0829822 | 4858.45ms | 108313 | 2560 | 4.13839e+06 | 48451.9 | 0.34123 | 1.42485 | 2(Loss) | true |
