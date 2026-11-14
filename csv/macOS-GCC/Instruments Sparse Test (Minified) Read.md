
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3368.42 | 0.113952 | 3143.35ms | 108313 | 1280 | 1.56301e+06 | 30665.8 | 0.143927 | 1(Win) | true |
| simdjson (ondemand) | 2806.38 | 0.0564108 | 3689.6ms | 108313 | 4890 | 2.10815e+06 | 36807.4 | 0.00908589 | 2(Loss) | true |
