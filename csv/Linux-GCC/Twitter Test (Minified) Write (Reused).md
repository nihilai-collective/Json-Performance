
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12671.1 | 0.267793 | 3610.44ms | 475954 | 320 | 2.94475e+06 | 35822 | 0.460075 | 0.195179 | 1(Win) | true |
| simdjson (reflection) | 9474.98 | 0.192044 | 4798.07ms | 475954 | 320 | 2.70847e+06 | 47905.7 | 0.293819 | 0.261104 | 2(Loss) | true |
| Glaze | 6021.9 | 0.455316 | 7684.53ms | 475954 | 80 | 9.42279e+06 | 75375.8 | 0.0420073 | 0.410975 | 3(Loss) | true |
