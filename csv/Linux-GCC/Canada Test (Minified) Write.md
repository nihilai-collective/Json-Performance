
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1812.44 | 0.0725435 | 6935.33ms | 2090326 | 80 | 5.09317e+07 | 1.09989e+06 | 0.374073 | 1.36597 | 1(Win) | true |
| Glaze | 1295.85 | 0.124519 | 9616.18ms | 2090234 | 80 | 2.93523e+08 | 1.5383e+06 | 0.502263 | 1.91052 | 2(Loss) | true |
| simdjson (reflection) | 1160.7 | 0.138867 | 5239.76ms | 2090326 | 40 | 2.27534e+08 | 1.71749e+06 | 1.78684 | 2.13298 | 3(Loss) | true |
