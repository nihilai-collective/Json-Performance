
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4451.06 | 0.31225 | 5257.75ms | 475954 | 2560 | 2.59567e+08 | 101977 | 1.39926 | 0.682631 | 1(Win) | true |
| Jsonifier | 3890.96 | 0.187189 | 6036.68ms | 475954 | 160 | 7.62952e+06 | 116656 | 0.162607 | 0.78029 | 2(Loss) | true |
