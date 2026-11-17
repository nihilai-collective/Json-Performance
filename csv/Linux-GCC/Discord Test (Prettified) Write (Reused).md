
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24986.3 | 0.0832645 | 362.219ms | 94370 | 40 | 359.785 | 3601.9 | 0.295158 | 0.0983353 | 1(Win) | true |
| Glaze | 5513.92 | 0.16476 | 1641.76ms | 94370 | 2560 | 1.85137e+06 | 16322 | 0.0194246 | 0.448282 | 2(Loss) | true |
| simdjson (reflection) | 532.02 | 0.170516 | 8742.12ms | 94370 | 160 | 1.33125e+07 | 169163 | 0.00791458 | 4.65255 | 3(Loss) | true |
