
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1676.77 | 0.230542 | 972.212ms | 4390 | 320 | 10603.2 | 2496.85 | 0.0399413 | 3.11438 | 13.8574 | 2.60205 | 0.00404399 | 1.70843e-05 | 7.11845e-07 | 1(Win) | true |
| simdjson (ondemand) | 1601.39 | 0.0300774 | 979.749ms | 4390 | 4890 | 3023.61 | 2614.38 | 0.00356039 | 3.25764 | 14.1203 | 2.44784 | 0.00459531 | 2.65988e-05 | 9.03708e-06 | 2(Loss) | true |
