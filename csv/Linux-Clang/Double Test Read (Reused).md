
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 712.822 | 0.0493175 | 960.435ms | 1811 | 1280 | 1827.62 | 2422.91 | 0.104427 | 7.31097 | 38.2518 | 6.19879 | 0.00102542 | 5.26298e-05 | 3.45113e-06 | 1(Win) | true |
| simdjson (ondemand) | 369.901 | 0.14672 | 1182.49ms | 1811 | 40 | 1877.17 | 4669.1 | 0.198146 | 13.788 | 70.2253 | 9.04362 | 0.000648813 | 6.90226e-05 | 1.38045e-05 | 2(Loss) | true |
