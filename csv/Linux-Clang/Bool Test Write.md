
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2249.35 | 0.617037 | 766.749ms | 905 | 40 | 224.215 | 383.7 | 0.0694505 | 2.48776 | 9.3105 | 0.950276 | 0.00436464 | 5.52486e-05 | 5.52486e-05 | 1(Win) | true |
| Glaze | 215.69 | 0.143741 | 1138.72ms | 905 | 2560 | 84690.8 | 4001.46 | 0.0273068 | 23.7823 | 112.617 | 22.8608 | 0.0770213 | 0.000800242 | 0.000466592 | 2(Loss) | true |
