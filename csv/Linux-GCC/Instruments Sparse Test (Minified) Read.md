
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5728.51 | 0.398511 | 1854.53ms | 108313 | 640 | 3.30474e+06 | 18031.8 | 0.0335631 | 0.431569 | 1(Win) | true |
| simdjson (ondemand) | 4811.38 | 0.0936425 | 2180.46ms | 108313 | 2560 | 1.03468e+06 | 21469 | 0.272859 | 0.513943 | 2(Loss) | true |
