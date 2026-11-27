
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 918.189 | 1.13544 | 6698.58ms | 4197496 | 40 | 9.80176e+10 | 4.35972e+06 | 0.33073 | 5.49525 | 26.9149 | 5.51385 | 0.000794533 | 0.0822276 | 0.00612753 | 1(Win) | true |
| simdjson (ondemand) | 747.178 | 0.700896 | 8256.35ms | 4197496 | 80 | 1.12805e+11 | 5.35755e+06 | 0.570384 | 6.7674 | 34.5338 | 5.38612 | 0.00850425 | 0.0818827 | 0.00668518 | 2(Loss) | true |
