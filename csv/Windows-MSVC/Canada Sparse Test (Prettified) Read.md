
----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11235.9 | 0.0535546 | 5626.04ms | 5212421 | 640 | 3.59283e+07 | 442417 | 0.0550548 | 0.270443 | 1(Win) | true |
| simdjson (ondemand) | 8619.7 | 0.0958634 | 7329.6ms | 5212421 | 320 | 9.78026e+07 | 576697 | 0.00606941 | 0.352554 | 2(Loss) | true |
