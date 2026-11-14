
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7341.54 | 0.363635 | 5999.2ms | 7351818 | 30 | 3.618e+08 | 955010 | 0.0716037 | 0.413893 | 1(Win) | true |
| simdjson (ondemand) | 5497.78 | 0.295354 | 8064.79ms | 7351818 | 40 | 5.67492e+08 | 1.27528e+06 | 0.0526957 | 0.552727 | 2(Loss) | true |
