
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2014.63 | 0.114918 | 46.3117ms | 905 | 640 | 155.118 | 428.405 | 0.0200559 | 1.15314 | 1(Win) | true |
| simdjson (reflection) | 258.575 | 0.13569 | 335.349ms | 905 | 4890 | 100306 | 3337.81 | 0.0730154 | 9.49848 | 2(Loss) | true |
| Glaze | 199.799 | 0.0507724 | 435.038ms | 905 | 40 | 192.41 | 4319.73 | 0.770406 | 12.3119 | 3(Loss) | true |
