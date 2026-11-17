
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3031.16 | 0.084094 | 125.821ms | 3862 | 40 | 41.7635 | 1215.08 | 0.308355 | 0.799236 | 1(Win) | true |
| Glaze | 1452.42 | 0.0663674 | 271.323ms | 3862 | 30 | 84.9713 | 2535.83 | 0.116853 | 1.6873 | 2(Loss) | true |
| Jsonifier (two-stage) | 821.307 | 0.115799 | 460.822ms | 3862 | 40 | 1078.66 | 4484.43 | 0.176041 | 2.9965 | 3(Loss) | true |
| simdjson (ondemand) | 421.294 | 0.0225683 | 898.614ms | 3862 | 30 | 116.782 | 8742.33 | 0.202814 | 5.85882 | 4(Loss) | true |
