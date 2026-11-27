
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10664.4 | 1.7571 | 854.305ms | 94370 | 4890 | 1.07522e+08 | 8439.14 | 0.885884 | 0.284228 | 1(Win) | true |
| Glaze | 3396.28 | 2.24118 | 2609.93ms | 94370 | 640 | 2.25733e+08 | 26499.1 | 0.131906 | 0.893568 | 2(Loss) | true |
