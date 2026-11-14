
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9418.67 | 0.192192 | 9471.06ms | 7351818 | 320 | 6.54988e+08 | 744398 | 0.207813 | 0.322616 | 1(Win) | true |
| simdjson (ondemand) | 8185.51 | 0.190722 | 5408.23ms | 7351818 | 160 | 4.26993e+08 | 856543 | 0.0584813 | 0.37123 | 2(Loss) | true |
