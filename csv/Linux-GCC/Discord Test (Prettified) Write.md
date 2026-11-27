
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18497.5 | 0.0946786 | 1228.75ms | 94370 | 320 | 6790.39 | 4865.42 | 0.0517309 | 0.280429 | 0.910522 | 0.119063 | 0.000161068 | 2.98029e-06 | 2.98029e-07 | 1(Win) | true |
| Glaze | 5769.03 | 0.0706649 | 2300.24ms | 94370 | 2560 | 311108 | 15600.2 | 0.2413 | 0.877037 | 3.65717 | 0.618163 | 0.000400791 | 6.54422e-06 | 2.29317e-06 | 2(Loss) | true |
| simdjson (reflection) | 564.37 | 0.1228 | 8560.68ms | 94370 | 2560 | 9.81687e+07 | 159467 | 0.27689 | 8.92835 | 38.8362 | 7.54198 | 0.0221409 | 0.00942239 | 0.000131646 | 3(Loss) | true |
