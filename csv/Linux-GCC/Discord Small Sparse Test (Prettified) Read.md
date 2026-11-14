
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4911.85 | 0.0667919 | 843.862ms | 6701 | 2560 | 1933.2 | 1301.05 | 0.02802 | 1.07908 | 4.49291 | 0.641099 | 0.000158092 | 1.61473e-05 | 1.69051e-06 | 1(Win) | true |
| simdjson (ondemand) | 4742.6 | 0.0884449 | 849.632ms | 6701 | 1280 | 1818.03 | 1347.48 | 0.039499 | 1.11644 | 4.75571 | 0.623042 | 0.000154478 | 1.78378e-05 | 1.98198e-06 | 2(Loss) | true |
