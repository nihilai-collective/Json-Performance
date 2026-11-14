
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3722.43 | 0.0556067 | 889.069ms | 6701 | 1280 | 1166.51 | 1716.77 | 0.0075092 | 1.41505 | 5.97269 | 1.00522 | 0.000385903 | 1.74881e-05 | 8.1611e-07 | 1(Win) | true |
| simdjson (ondemand) | 3022.59 | 0.0221343 | 925.943ms | 6701 | 1280 | 280.327 | 2114.27 | 0.178534 | 1.7361 | 7.77018 | 1.23802 | 0.00126229 | 1.73715e-05 | 6.52888e-06 | 2(Loss) | true |
