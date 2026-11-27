
----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24218.3 | 0.10137 | 754.317ms | 9249 | 4890 | 666.543 | 364.21 | 0.029472 | 0.236299 | 0.74181 | 0.0934155 | 0.000108208 | 2.04963e-05 | 3.8251e-06 | 1(Win) | true |
| Glaze | 2998.85 | 0.152321 | 1012.9ms | 9249 | 2560 | 51385.5 | 2941.31 | 0.241125 | 1.746 | 3.78863 | 0.623527 | 0.000328541 | 5.32152e-05 | 2.4876e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.32 | 0.0695365 | 2414.91ms | 9249 | 4890 | 669162 | 16822.8 | 0.192218 | 9.85842 | 40.8036 | 8.29099 | 0.0144181 | 0.000151368 | 7.48216e-05 | 3(Loss) | true |
