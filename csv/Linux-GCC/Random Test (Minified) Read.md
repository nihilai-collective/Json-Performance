
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1254.2 | 0.3178 | 8599.58ms | 461466 | 320 | 3.97927e+08 | 350891 | 0.678023 | 1.97375 | 1(Win) | true |
| Jsonifier (two-stage) | 1101.43 | 0.200926 | 5084.59ms | 461466 | 640 | 4.12498e+08 | 399562 | 0.093868 | 2.24759 | 2(Loss) | true |
| simdjson (reflection) | 1063.44 | 0.136885 | 5301.42ms | 461466 | 320 | 1.02688e+08 | 413836 | 0.342888 | 2.32789 | 3(Loss) | true |
| simdjson (ondemand) | 1057.75 | 0.166271 | 5242.36ms | 461466 | 320 | 1.53143e+08 | 416062 | 1.09325 | 2.3404 | 4(Loss) | true |
| Glaze | 960.908 | 0.460172 | 5811.29ms | 461466 | 30 | 1.33253e+08 | 457992 | 0.173326 | 2.57631 | 5(Loss) | true |
