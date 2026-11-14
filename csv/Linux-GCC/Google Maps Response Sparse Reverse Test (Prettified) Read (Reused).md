
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3479.23 | 0.0256676 | 1428.76ms | 25388 | 4890 | 15601.6 | 6958.99 | 0.0101404 | 1.4819 | 7.09918 | 1.24941 | 0.0035031 | 1.35806e-05 | 4.41411e-06 | 1(Win) | true |
| simdjson (ondemand) | 3294.85 | 0.0641389 | 1470.17ms | 25388 | 640 | 14217.1 | 7348.41 | 0.020876 | 1.56538 | 7.1197 | 1.1416 | 0.00347531 | 4.61586e-06 | 1.84634e-07 | 2(Loss) | true |
