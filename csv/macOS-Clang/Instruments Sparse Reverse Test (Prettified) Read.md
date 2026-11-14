
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2374.09 | 0.623132 | 6448.71ms | 183677 | 30 | 6.34159e+06 | 73783.4 | 0.898399 | 1(Win) | true |
| simdjson (ondemand) | 1961.57 | 0.630605 | 8231.62ms | 183677 | 80 | 2.53693e+07 | 89300.1 | 1.59655 | 2(Loss) | true |
