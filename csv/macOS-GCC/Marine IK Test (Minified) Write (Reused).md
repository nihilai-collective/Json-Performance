
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1302.5 | 0.269018 | 8665.83ms | 1834197 | 80 | 1.04421e+09 | 1.34298e+06 | 0.512514 | 1(Win) | true |
| Glaze | 862.316 | 1.49638 | 6269.17ms | 1833577 | 30 | 2.76229e+10 | 2.02784e+06 | 2.73216 | 2(Loss) | true |
| simdjson (reflection) | 755.967 | 0.636287 | 7907.21ms | 1922245 | 80 | 1.90462e+10 | 2.42497e+06 | 2.60391 | 3(Loss) | true |
