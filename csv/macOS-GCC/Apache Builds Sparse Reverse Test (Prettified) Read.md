
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1361.3 | 0.449031 | 8200.78ms | 124597 | 640 | 9.83201e+07 | 87288 | 0.13307 | 1(Win) | true |
| simdjson (ondemand) | 1018.83 | 0.42646 | 5667.46ms | 124597 | 640 | 1.58324e+08 | 116629 | 0.752258 | 2(Loss) | true |
