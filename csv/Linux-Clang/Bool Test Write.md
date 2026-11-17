
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.78 | 0.117189 | 44.6796ms | 905 | 160 | 34.7344 | 397.587 | 0.00314386 | 1.0611 | 1(Win) | true |
| Glaze | 186.817 | 0.568998 | 545.491ms | 905 | 640 | 442248 | 4619.89 | 0.0844888 | 13.1732 | 2(Loss) | true |
