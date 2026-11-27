
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4889.61 | 0.164478 | 9077.54ms | 7351818 | 320 | 1.77994e+09 | 1.4339e+06 | 0.0763156 | 1(Win) | true |
| simdjson (ondemand) | 3691.86 | 0.167968 | 5952.35ms | 7351818 | 160 | 1.62807e+09 | 1.89911e+06 | 0.0826747 | 2(Loss) | true |
