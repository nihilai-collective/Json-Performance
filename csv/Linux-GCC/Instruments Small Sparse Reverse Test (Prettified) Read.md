
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4684.84 | 0.157574 | 878.67ms | 7932 | 80 | 517.888 | 1614.69 | 0.0487948 | 1.12731 | 5.0474 | 0.816944 | 0.000893533 | 7.87948e-06 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 3886.52 | 0.0458285 | 914.659ms | 7932 | 4890 | 3890.67 | 1946.36 | 0.0238491 | 1.33861 | 6.12822 | 0.930661 | 0.00165311 | 1.07767e-05 | 1.49533e-06 | 2(Loss) | true |
