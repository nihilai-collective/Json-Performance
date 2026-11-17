
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1490.96 | 0.468895 | 3627.5ms | 56369 | 160 | 4.57318e+06 | 36055.6 | 0.0779437 | 1.65892 | 1(Win) | true |
| simdjson (ondemand) | 1292.74 | 0.202259 | 4245.03ms | 56369 | 640 | 4.52749e+06 | 41584.4 | 0.0526316 | 1.91308 | 2(Loss) | true |
