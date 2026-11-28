
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2231.54 | 0.0501083 | 41.9908ms | 905 | 640 | 24.0374 | 386.762 | 0.154894 | 1.03639 | 1(Win) | true |
| Glaze | 198.489 | 0.679537 | 427.505ms | 905 | 1280 | 1.11753e+06 | 4348.23 | 0.627461 | 12.3985 | 2(Loss) | true |
