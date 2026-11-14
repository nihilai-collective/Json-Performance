
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2385.39 | 0.0392672 | 192.17ms | 4669 | 640 | 343.852 | 1866.66 | 0.0558628 | 1(Win) | true |
| simdjson (ondemand) | 1750.27 | 0.0699456 | 259.825ms | 4669 | 160 | 506.616 | 2544.01 | 0.0903267 | 2(Loss) | true |
