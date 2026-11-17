
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2643.42 | 0.0701783 | 6402.46ms | 676745 | 320 | 9.3945e+06 | 244151 | 0.0721154 | 1.91837 | 8.60411 | 1.5369 | 0.00578853 | 0.000530296 | 4.41913e-06 | 1(Win) | true |
| simdjson (ondemand) | 2229.13 | 0.0579485 | 7583.5ms | 676745 | 320 | 9.00773e+06 | 289528 | 0.0239492 | 2.2907 | 9.46257 | 1.6358 | 0.00910186 | 0.00190225 | 2.87728e-05 | 2(Loss) | true |
