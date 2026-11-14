
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13497 | 0.172848 | 673.219ms | 94370 | 4890 | 649585 | 6668.04 | 0.0892883 | 1(Win) | true |
| Glaze | 2282.92 | 0.477286 | 3998.94ms | 94370 | 160 | 5.66453e+06 | 39422.4 | 0.0527341 | 2(Loss) | true |
| simdjson (reflection) | 332.67 | 0.101855 | 7014.77ms | 94370 | 1280 | 9.71897e+07 | 270533 | 0.0401268 | 3(Loss) | true |
