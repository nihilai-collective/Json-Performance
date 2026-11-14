
----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9063.08 | 0.150395 | 7123.2ms | 5212421 | 80 | 5.44357e+07 | 548484 | 0.265606 | 0.566239 | 2.54445 | 0.309603 | 0.00221432 | 0.0591118 | 1.55878e-06 | 1(Win) | true |
| simdjson (ondemand) | 7950.73 | 0.0841107 | 8074.9ms | 5212421 | 80 | 2.21237e+07 | 625220 | 0.256357 | 0.646142 | 2.85498 | 0.331081 | 0.00215496 | 0.059186 | 3.68831e-06 | 2(Loss) | true |
