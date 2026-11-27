
----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3673.37 | 0.15044 | 7192.18ms | 2090234 | 160 | 1.06637e+08 | 542662 | 0.101529 | 1(Win) | true |
| simdjson (ondemand) | 2919.96 | 0.101913 | 8497.16ms | 2090234 | 640 | 3.09798e+08 | 682682 | 0.0111338 | 2(Loss) | true |
