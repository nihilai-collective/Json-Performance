
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8307.92 | 0.170428 | 6108.04ms | 2090234 | 80 | 1.33776e+07 | 239940 | 0.0333528 | 0.365751 | 1(Win) | true |
| simdjson (ondemand) | 6425.44 | 0.0838316 | 7929.36ms | 2090234 | 320 | 2.16446e+07 | 310236 | 0.100126 | 0.472937 | 2(Loss) | true |
