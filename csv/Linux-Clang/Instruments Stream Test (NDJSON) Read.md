
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1710.63 | 0.892519 | 7650.1ms | 4197496 | 80 | 3.48974e+10 | 2.3401e+06 | 0.166736 | 2.95351 | 15.4784 | 2.85201 | 0.000470724 | 0.0819059 | 0.0022422 | 1(Win) | true |
| simdjson (ondemand) | 1351.63 | 0.873323 | 9513.77ms | 4197496 | 160 | 1.07037e+11 | 2.96164e+06 | 0.319213 | 3.74715 | 18.5261 | 2.73403 | 0.00565131 | 0.0814562 | 0.00397221 | 2(Loss) | true |
