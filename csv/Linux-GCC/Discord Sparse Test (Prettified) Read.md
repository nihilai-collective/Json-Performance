
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3094.16 | 0.116746 | 2639.8ms | 83958 | 1280 | 1.16823e+06 | 25877.3 | 1.37236 | 0.799289 | 1(Win) | true |
| simdjson (ondemand) | 2909.01 | 0.0981148 | 2756.44ms | 83958 | 2560 | 1.867e+06 | 27524.4 | 0.190503 | 0.850229 | 2(Loss) | true |
