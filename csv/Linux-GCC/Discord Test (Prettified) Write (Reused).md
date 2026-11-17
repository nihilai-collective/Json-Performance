
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20624.1 | 0.0724667 | 1178.7ms | 94370 | 30 | 299.995 | 4363.73 | 0.0244379 | 0.247554 | 0.894532 | 0.132871 | 0.000105966 | 1.34223e-05 | 8.12405e-06 | 1(Win) | true |
| Glaze | 7150.07 | 0.134791 | 2003.76ms | 94370 | 1280 | 368453 | 12587 | 0.0667342 | 0.708158 | 3.60407 | 0.605966 | 0.000362205 | 1.26166e-05 | 6.79672e-06 | 2(Loss) | true |
| simdjson (reflection) | 559.093 | 0.153384 | 8618.59ms | 94370 | 2560 | 1.56062e+08 | 160972 | 0.168406 | 9.01512 | 38.8305 | 7.53866 | 0.0230107 | 0.017364 | 0.000647447 | 3(Loss) | true |
