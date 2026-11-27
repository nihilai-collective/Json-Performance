
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14107.8 | 0.17187 | 926.693ms | 136037 | 1280 | 319747 | 9196 | 0.0260915 | 1(Win) | true |
| Glaze | 4396.55 | 0.258252 | 2827.83ms | 136076 | 160 | 929704 | 29516.8 | 0.141136 | 2(Loss) | true |
| simdjson (reflection) | 392.215 | 0.073326 | 8535.48ms | 136037 | 1280 | 7.52996e+07 | 330775 | 0.0866906 | 3(Loss) | true |
