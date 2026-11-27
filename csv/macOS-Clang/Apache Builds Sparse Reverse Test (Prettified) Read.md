
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1832.82 | 0.0560094 | 6552.2ms | 124597 | 4890 | 6.44773e+06 | 64831.8 | 0.181336 | 1(Win) | true |
| simdjson (ondemand) | 1534.22 | 0.0602081 | 8135.65ms | 124597 | 4890 | 1.06331e+07 | 77450 | 0.38758 | 2(Loss) | true |
