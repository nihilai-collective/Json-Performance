
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15682 | 0.121494 | 933.055ms | 31235 | 2560 | 13634.2 | 1899.51 | 0.0357745 | 0.329044 | 1.41972 | 0.26307 | 6.59567e-05 | 1.38316e-05 | 5.8403e-06 | 1(Win) | true |
| Glaze | 5243.95 | 0.0716324 | 1313.38ms | 31235 | 2560 | 42386.2 | 5680.45 | 0.0374568 | 0.971478 | 3.70312 | 0.653946 | 0.00226555 | 2.05599e-05 | 1.02049e-05 | 2(Loss) | true |
