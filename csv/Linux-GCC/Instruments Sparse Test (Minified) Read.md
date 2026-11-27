
----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5342.08 | 0.0185975 | 2659.79ms | 108313 | 4890 | 63235.4 | 19336.2 | 0.025252 | 0.959853 | 5.24191 | 0.807493 | 0.000860097 | 5.11469e-06 | 2.76975e-06 | 1(Win) | true |
| simdjson (ondemand) | 4444.37 | 0.032177 | 3050.56ms | 108313 | 1280 | 71588.3 | 23241.8 | 0.182235 | 1.14291 | 5.90505 | 0.771025 | 0.00148517 | 2.87794e-06 | 8.29483e-07 | 2(Loss) | true |
