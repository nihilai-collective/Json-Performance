
----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.71 | 0.0828227 | 3669.5ms | 56369 | 4890 | 3.53178e+06 | 32448.4 | 0.0483565 | 1.83298 | 1(Win) | true |
| simdjson (ondemand) | 1120.89 | 0.117753 | 5212.8ms | 56369 | 2560 | 8.16473e+06 | 47959.8 | 0.207831 | 2.70989 | 2(Loss) | true |
