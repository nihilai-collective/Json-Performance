
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11187.2 | 0.0354897 | 1651.61ms | 108313 | 2560 | 27489.5 | 9233.39 | 0.0691245 | 0.461998 | 2.40686 | 0.163739 | 1.95109e-05 | 1.77437e-06 | 2.38025e-07 | 1(Win) | true |
| simdjson (stage-1) | 10654 | 0.061298 | 1691.92ms | 108313 | 320 | 11302.6 | 9695.47 | 0.0068004 | 0.485103 | 2.67105 | 0.109018 | 5.44718e-05 | 1.99076e-06 | 8.65547e-08 | 2(Loss) | true |
