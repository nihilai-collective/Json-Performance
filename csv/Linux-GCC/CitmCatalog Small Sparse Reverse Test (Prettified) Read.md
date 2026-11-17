
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5157.52 | 0.15143 | 901.988ms | 9739 | 1280 | 9518.82 | 1800.83 | 0.000216914 | 1.00938 | 4.68703 | 0.749153 | 0.00132008 | 1.66855e-05 | 3.93072e-06 | 1(Win) | true |
| simdjson (ondemand) | 5139.39 | 0.0931577 | 903.048ms | 9739 | 2560 | 7255.77 | 1807.19 | 0.430677 | 1.01486 | 5.00647 | 0.712599 | 0.00125907 | 3.14457e-05 | 1.56025e-05 | 2(Loss) | true |
