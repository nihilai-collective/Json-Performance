
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7144.1 | 0.657158 | 162.589ms | 11812 | 1280 | 137436 | 1576.8 | 0.644875 | 0.340715 | 1(Win) | true |
| Glaze | 2769.47 | 0.251698 | 410.058ms | 11812 | 2560 | 268322 | 4067.5 | 0.461167 | 0.88779 | 2(Loss) | true |
