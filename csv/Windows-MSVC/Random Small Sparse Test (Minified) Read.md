
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1215.1 | 0.126452 | 395.325ms | 4926 | 4890 | 116876 | 3866.18 | 0.659331 | 2.48799 | 1(Win) | true |
| simdjson (ondemand) | 1156.61 | 0.151845 | 408.698ms | 4926 | 4890 | 186004 | 4061.7 | 0.165669 | 2.61506 | 2(Loss) | true |
