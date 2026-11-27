
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13993.9 | 0.120516 | 1141.79ms | 58581 | 320 | 7407.62 | 3992.26 | 0.0921247 | 0.365164 | 1.10848 | 0.165275 | 3.22203e-05 | 6.93484e-06 | 2.6139e-06 | 1(Win) | true |
| simdjson (reflection) | 11536.4 | 0.0854177 | 1226.43ms | 58581 | 1280 | 21901.9 | 4842.71 | 0.0695795 | 0.443168 | 1.48249 | 0.207678 | 3.17669e-05 | 2.98865e-05 | 1.84173e-05 | 2(Loss) | true |
| Glaze | 7298.94 | 0.104751 | 1507.29ms | 58581 | 1280 | 82284.4 | 7654.15 | 0.140828 | 0.694833 | 2.43669 | 0.371264 | 3.51543e-05 | 1.39764e-05 | 6.2947e-06 | 3(Loss) | true |
