
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14196.2 | 0.154494 | 6460.69ms | 7351818 | 160 | 9.31511e+07 | 493882 | 0.364069 | 0.360654 | 1.54566 | 0.0821143 | 0.00229367 | 0.0211532 | 0.000134661 | 1(Win) | true |
| simdjson (stage-1) | 13826.8 | 0.130143 | 6587.74ms | 7351818 | 80 | 3.48398e+07 | 507075 | 0.0210812 | 0.368943 | 1.7809 | 0.0660418 | 0.00106483 | 0.021181 | 4.4018e-05 | 2(Loss) | true |
