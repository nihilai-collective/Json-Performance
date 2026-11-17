
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1182.76 | 0.781037 | 5301.57ms | 2090234 | 160 | 2.77245e+10 | 1.68539e+06 | 2.25656 | 2.09308 | 1(Win) | true |
| Glaze | 773.934 | 0.29584 | 8118.2ms | 2090234 | 30 | 1.74188e+09 | 2.57568e+06 | 1.17118 | 3.19878 | 2(Loss) | true |
