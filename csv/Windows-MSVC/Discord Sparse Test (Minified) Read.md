
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.12 | 0.120939 | 4012.09ms | 56369 | 2560 | 5.58343e+06 | 38615.7 | 0.220037 | 1.77648 | 1(Win) | true |
| simdjson (ondemand) | 1253.83 | 0.0982824 | 4509.78ms | 56369 | 4890 | 8.68293e+06 | 42874.9 | 2.40762 | 1.97228 | 2(Loss) | true |
