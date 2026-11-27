
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11699.3 | 0.065947 | 38.6135ms | 4390 | 640 | 35.6435 | 357.853 | 0.228442 | 0.196635 | 1(Win) | true |
| Glaze | 3030.59 | 0.158081 | 141.128ms | 4390 | 160 | 763.055 | 1381.46 | 0.126066 | 0.801842 | 2(Loss) | true |
