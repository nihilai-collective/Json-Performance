
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13318.8 | 0.294697 | 3288.69ms | 475954 | 2560 | 2.58221e+07 | 34080.1 | 0.0419776 | 1(Win) | true |
| simdjson (reflection) | 11356.7 | 0.647125 | 3949.47ms | 475954 | 40 | 2.67584e+06 | 39968 | 1.06147 | 2(Loss) | true |
| Glaze | 3922.71 | 0.370287 | 5728.13ms | 475954 | 80 | 1.46867e+07 | 115712 | 0.0996567 | 3(Loss) | true |
