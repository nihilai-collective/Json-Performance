
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2150.11 | 0.0556365 | 3732.51ms | 83958 | 1280 | 549454 | 37239.2 | 0.00923171 | 1.41261 | 1(Win) | true |
| simdjson (ondemand) | 1959.48 | 0.0993843 | 4092.58ms | 83958 | 640 | 1.0555e+06 | 40862.2 | 0.0803649 | 1.55016 | 2(Loss) | true |
