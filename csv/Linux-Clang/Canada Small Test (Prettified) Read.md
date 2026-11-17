
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1805.19 | 0.0252962 | 1345.55ms | 11579 | 4890 | 11708.9 | 6117.14 | 0.0268917 | 2.83243 | 13.5809 | 2.31298 | 0.00196883 | 1.835e-05 | 5.45731e-06 | 1(Win) | true |
| Jsonifier (generic) | 1729.6 | 0.0783572 | 1375.46ms | 11579 | 640 | 16017.3 | 6384.49 | 0.0340064 | 2.9545 | 13.9007 | 2.59811 | 0.00261519 | 2.1051e-05 | 2.15908e-06 | 2(Loss) | true |
