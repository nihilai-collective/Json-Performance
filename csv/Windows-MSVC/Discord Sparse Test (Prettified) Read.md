
----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2136.19 | 0.176546 | 3776.97ms | 83958 | 160 | 700613 | 37481.9 | 0.224603 | 1.42174 | 1(Win) | true |
| simdjson (ondemand) | 2044.24 | 0.0998784 | 3926.51ms | 83958 | 2560 | 3.91781e+06 | 39167.9 | 0.143009 | 1.48582 | 2(Loss) | true |
