
----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2731.68 | 0.0959368 | 8208.85ms | 1834197 | 160 | 6.03842e+07 | 640349 | 0.0760163 | 1(Win) | true |
| Jsonifier (generic) | 2337.92 | 1.15442 | 9893.04ms | 1834197 | 80 | 5.96835e+09 | 748198 | 3.5281 | 2(Loss) | true |
