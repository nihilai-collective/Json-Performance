
----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4440.8 | 0.265737 | 5052.26ms | 1834197 | 160 | 1.75305e+08 | 393899 | 0.132314 | 0.684303 | 1(Win) | true |
| simdjson (ondemand) | 4111.02 | 0.210524 | 5477.2ms | 1834197 | 160 | 1.28385e+08 | 425497 | 0.14401 | 0.739195 | 2(Loss) | true |
