
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9539.82 | 0.038887 | 1398.2ms | 65103 | 2560 | 16397.3 | 6508.2 | 0.0657476 | 0.539286 | 2.54236 | 0.30567 | 0.000620639 | 3.59406e-06 | 6.24011e-07 | 1(Win) | true |
| simdjson (ondemand) | 7985.63 | 0.0398948 | 1530.75ms | 65103 | 80 | 769.673 | 7774.85 | 0.218177 | 0.648589 | 2.92646 | 0.327804 | 0.000695436 | 4.03207e-06 | 1.15202e-06 | 2(Loss) | true |
