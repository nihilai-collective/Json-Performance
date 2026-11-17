
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14109.2 | 1.28507 | 526.737ms | 78778 | 160 | 749171 | 5324.8 | 2.84302 | 1(Win) | true |
| Glaze | 3928 | 0.910159 | 2070.13ms | 78778 | 80 | 2.42432e+06 | 19126.4 | 0.285235 | 2(Loss) | true |
| simdjson (reflection) | 397.724 | 1.08459 | 5251.13ms | 78778 | 40 | 1.67894e+08 | 188896 | 0.582727 | 3(Loss) | true |
