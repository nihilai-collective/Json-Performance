
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8757.88 | 0.245472 | 5985.18ms | 2090234 | 30 | 9.36522e+06 | 227612 | 0.52977 | 0.282658 | 1(Win) | true |
| simdjson (ondemand) | 7196.66 | 0.177091 | 7003.75ms | 2090234 | 40 | 9.62457e+06 | 276990 | 0.0663542 | 0.343978 | 2(Loss) | true |
