
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3736.89 | 0.0695592 | 890.502ms | 6701 | 1280 | 1811.25 | 1710.13 | 0.0132922 | 1.40948 | 5.97269 | 1.00522 | 0.000368415 | 1.56227e-05 | 2.09857e-06 | 1(Win) | true |
| simdjson (ondemand) | 2992.08 | 0.0350248 | 932.114ms | 6701 | 4890 | 2736.48 | 2135.83 | 0.203429 | 1.75287 | 7.77556 | 1.24086 | 0.00124512 | 1.60523e-05 | 3.29591e-06 | 2(Loss) | true |
