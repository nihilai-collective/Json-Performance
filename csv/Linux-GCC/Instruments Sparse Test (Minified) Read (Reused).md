
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5229 | 0.0493674 | 2720.95ms | 108313 | 320 | 30433.6 | 19754.3 | 0.00417613 | 0.986409 | 5.40314 | 0.772456 | 0.000850025 | 1.8465e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4630.85 | 0.0758397 | 2973.34ms | 108313 | 160 | 45788.3 | 22305.9 | 0.0470785 | 1.11388 | 5.78547 | 0.732193 | 0.0013622 | 1.01558e-05 | 8.42466e-06 | 2(Loss) | true |
