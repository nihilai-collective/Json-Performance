
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2533.96 | 0.350224 | 6478.74ms | 183677 | 1280 | 7.5026e+07 | 69128.2 | 0.0368892 | 1(Win) | true |
| simdjson (ondemand) | 2041.97 | 0.21024 | 8061.8ms | 183677 | 1280 | 4.16341e+07 | 85783.7 | 1.55395 | 2(Loss) | true |
