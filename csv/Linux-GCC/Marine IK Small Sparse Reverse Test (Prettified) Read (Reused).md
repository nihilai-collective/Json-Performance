
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7946.96 | 0.0438329 | 939.354ms | 18245 | 4890 | 4503.97 | 2189.49 | 0.0714983 | 0.658905 | 3.20088 | 0.44741 | 0.000329911 | 9.11251e-06 | 7.39761e-07 | 1(Win) | true |
| simdjson (ondemand) | 5789.23 | 0.0649061 | 1019.35ms | 18245 | 4890 | 18609.2 | 3005.54 | 0.0872015 | 0.900804 | 4.37638 | 0.631242 | 0.000388879 | 9.00042e-06 | 1.00876e-06 | 2(Loss) | true |
