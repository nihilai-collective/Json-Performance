
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2509.87 | 0.599654 | 6713.63ms | 676745 | 80 | 1.90213e+08 | 257143 | 0.490918 | 1(Win) | true |
| simdjson (ondemand) | 2027.7 | 0.131664 | 8236.52ms | 676745 | 80 | 1.40498e+07 | 318290 | 0.00882922 | 2(Loss) | true |
