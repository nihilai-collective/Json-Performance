
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2154.95 | 0.0905441 | 3716.95ms | 83958 | 2560 | 2.89742e+06 | 37155.7 | 0.0315296 | 1.40941 | 1(Win) | true |
| simdjson (ondemand) | 2089.64 | 0.0629939 | 3838.58ms | 83958 | 2560 | 1.49148e+06 | 38317 | 0.0581429 | 1.45354 | 2(Loss) | true |
