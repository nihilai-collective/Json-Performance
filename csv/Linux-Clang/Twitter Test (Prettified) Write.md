
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16457.1 | 0.108643 | 4217.32ms | 716365 | 2560 | 5.20727e+06 | 41512.8 | 0.0390977 | 0.150343 | 1(Win) | true |
| Glaze | 4761.09 | 0.0666686 | 7363.06ms | 716365 | 2560 | 2.34282e+07 | 143492 | 0.191053 | 0.51987 | 2(Loss) | true |
