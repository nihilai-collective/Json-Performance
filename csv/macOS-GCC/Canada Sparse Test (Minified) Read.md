
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3953.01 | 0.362067 | 6486.46ms | 2090234 | 320 | 1.06675e+09 | 504274 | 2.51313 | 1(Win) | true |
| simdjson (ondemand) | 3017.88 | 0.784736 | 7776.38ms | 2090234 | 160 | 4.29887e+09 | 660531 | 2.98863 | 2(Loss) | true |
