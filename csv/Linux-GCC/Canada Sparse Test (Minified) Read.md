
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10430.2 | 0.15235 | 9536.81ms | 2090234 | 1280 | 1.08516e+08 | 191117 | 0.340281 | 0.23733 | 1(Win) | true |
| simdjson (ondemand) | 8241.65 | 0.357778 | 6092.5ms | 2090234 | 40 | 2.99536e+07 | 241869 | 0.43566 | 0.300348 | 2(Loss) | true |
