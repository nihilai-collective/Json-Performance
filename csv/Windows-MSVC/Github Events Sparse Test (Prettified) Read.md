
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5706.53 | 0.207076 | 1092.54ms | 65103 | 80 | 40607.6 | 10880 | 0.115022 | 0.531404 | 1(Win) | true |
| simdjson (ondemand) | 5212.75 | 0.0674231 | 1194.57ms | 65103 | 2560 | 165092 | 11910.6 | 0.124782 | 0.581868 | 2(Loss) | true |
