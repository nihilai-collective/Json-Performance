
----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8739.19 | 0.116497 | 7230.27ms | 5212421 | 320 | 1.40513e+08 | 568811 | 0.267167 | 0.347731 | 1(Win) | true |
| simdjson (ondemand) | 6992.73 | 0.0741125 | 9045.25ms | 5212421 | 640 | 1.77643e+08 | 710874 | 0.144265 | 0.434591 | 2(Loss) | true |
