
----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2184.22 | 0.0232272 | 3487.32ms | 56369 | 2560 | 83660.8 | 24611.8 | 0.376763 | 2.35649 | 11.5663 | 2.15698 | 0.00435685 | 8.50285e-06 | 3.76287e-06 | 1(Win) | true |
| simdjson (ondemand) | 1494.76 | 0.0368098 | 4596.69ms | 56369 | 1280 | 224325 | 35964.2 | 0.112356 | 3.41869 | 15.1001 | 2.64941 | 0.00959944 | 1.0464e-05 | 4.13015e-06 | 2(Loss) | true |
