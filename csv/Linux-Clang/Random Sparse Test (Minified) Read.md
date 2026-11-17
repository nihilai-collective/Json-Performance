
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2499.5 | 0.250884 | 8184.68ms | 409725 | 80 | 1.23059e+07 | 156329 | 0.390362 | 0.990268 | 1(Win) | true |
| simdjson (ondemand) | 1900.24 | 0.084108 | 5280.98ms | 409725 | 1280 | 3.82871e+07 | 205629 | 0.250195 | 1.30262 | 2(Loss) | true |
