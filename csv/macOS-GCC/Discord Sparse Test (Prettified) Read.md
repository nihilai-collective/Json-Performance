
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2302.3 | 0.688589 | 3867.42ms | 83958 | 40 | 2.29393e+06 | 34777.6 | 0.232558 | 1(Win) | true |
| simdjson (ondemand) | 1752.57 | 0.240998 | 4758.32ms | 83958 | 4890 | 5.92801e+07 | 45686.3 | 0.633321 | 2(Loss) | true |
