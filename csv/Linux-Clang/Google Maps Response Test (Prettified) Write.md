
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17813.3 | 0.104473 | 171.201ms | 31235 | 30 | 91.5644 | 1672.23 | 0.00398684 | 0.136762 | 1(Win) | true |
| Glaze | 5325.79 | 0.171444 | 564.206ms | 31235 | 2560 | 235396 | 5593.17 | 0.115179 | 0.462727 | 2(Loss) | true |
