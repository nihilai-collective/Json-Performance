
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4040.41 | 0.045119 | 882.613ms | 6701 | 640 | 325.932 | 1581.66 | 0.0224199 | 1.30747 | 5.5726 | 0.913147 | 0.000882098 | 1.469e-05 | 1.16587e-06 | 1(Win) | true |
| simdjson (ondemand) | 3154.13 | 0.0559774 | 923.102ms | 6701 | 2560 | 3292.96 | 2026.1 | 0.011762 | 1.66434 | 7.37994 | 1.15207 | 0.00206557 | 1.48649e-05 | 1.98198e-06 | 2(Loss) | true |
