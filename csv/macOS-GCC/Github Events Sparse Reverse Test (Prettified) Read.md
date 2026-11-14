
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4032.05 | 0.527582 | 1553.57ms | 65103 | 40 | 263992 | 15398.4 | 0.468836 | 1(Win) | true |
| simdjson (ondemand) | 3108.71 | 0.201831 | 2059.31ms | 65103 | 320 | 519958 | 19972 | 0.163961 | 2(Loss) | true |
