
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3854.39 | 0.156494 | 768.223ms | 2158 | 160 | 111.714 | 533.944 | 0.064338 | 1.43709 | 5.54727 | 0.950417 | 0.000619787 | 1.73772e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 3129.2 | 0.0810838 | 781.155ms | 2158 | 1280 | 364.011 | 657.685 | 0.0229208 | 1.74708 | 6.90825 | 1.14643 | 0.00049706 | 3.36683e-05 | 1.08608e-05 | 2(Loss) | true |
