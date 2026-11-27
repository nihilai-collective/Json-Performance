
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4619.61 | 0.178988 | 79.8508ms | 3770 | 2560 | 4967.74 | 778.281 | 0.241497 | 0.641104 | 1(Win) | true |
| simdjson (ondemand) | 3723.34 | 0.28292 | 106.383ms | 3770 | 320 | 2388.32 | 965.625 | 0.259572 | 0.801005 | 2(Loss) | true |
