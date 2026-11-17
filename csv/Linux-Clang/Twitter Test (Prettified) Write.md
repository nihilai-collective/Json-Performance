
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15684.9 | 0.544684 | 4240.35ms | 716365 | 80 | 4.50284e+06 | 43556.6 | 0.206825 | 0.157734 | 1(Win) | true |
| Glaze | 4623.35 | 0.271617 | 7744.1ms | 716365 | 160 | 2.57744e+07 | 147767 | 0.312643 | 0.535354 | 2(Loss) | true |
