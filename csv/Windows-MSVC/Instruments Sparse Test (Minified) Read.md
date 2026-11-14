
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3752.7 | 0.0566875 | 2770.09ms | 108313 | 4890 | 1.19058e+06 | 27525.6 | 0.218781 | 0.809211 | 1(Win) | true |
| simdjson (ondemand) | 3254.84 | 0.210342 | 3193.87ms | 108313 | 320 | 1.42595e+06 | 31735.9 | 0.00295415 | 0.932932 | 2(Loss) | true |
