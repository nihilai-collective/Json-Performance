
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1970.75 | 0.0909846 | 8828.51ms | 676745 | 160 | 1.4205e+07 | 327486 | 0.164377 | 1(Win) | true |
| simdjson (ondemand) | 1487.38 | 0.0803659 | 5620.3ms | 676745 | 320 | 3.89133e+07 | 433913 | 0.00755969 | 2(Loss) | true |
