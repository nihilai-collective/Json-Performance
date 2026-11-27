
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18757.3 | 0.0695727 | 1213.8ms | 94370 | 160 | 1782.89 | 4798.04 | 0.0138096 | 0.277052 | 0.904864 | 0.117792 | 0.000156498 | 4.56978e-06 | 2.84783e-06 | 1(Win) | true |
| Glaze | 7086.21 | 0.0299809 | 2007.74ms | 94370 | 4890 | 70898.5 | 12700.5 | 0.155849 | 0.720806 | 3.60407 | 0.605966 | 0.000294802 | 6.0199e-06 | 2.32085e-06 | 2(Loss) | true |
| simdjson (reflection) | 562.009 | 0.172811 | 8579.49ms | 94370 | 1280 | 9.80246e+07 | 160137 | 0.435341 | 8.93601 | 38.8342 | 7.54117 | 0.0222478 | 0.0135772 | 0.000150885 | 3(Loss) | true |
