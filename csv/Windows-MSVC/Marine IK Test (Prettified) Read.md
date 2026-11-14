
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2086.81 | 0.469576 | 5027.36ms | 7351818 | 80 | 1.99124e+10 | 3.35978e+06 | 1.02247 | 1.45636 | 1(Win) | true |
| Jsonifier | 2009.1 | 0.374966 | 5219.96ms | 7351818 | 80 | 1.36981e+10 | 3.48974e+06 | 0.548955 | 1.51268 | 2(Loss) | true |
| simdjson (ondemand) | 1318.33 | 0.443285 | 8049.86ms | 7351818 | 40 | 2.22314e+10 | 5.31826e+06 | 1.09827 | 2.30542 | 3(Loss) | true |
| Glaze | 1127.56 | 0.405467 | 9321.49ms | 7351818 | 80 | 5.08522e+10 | 6.21806e+06 | 0.840408 | 2.6955 | 4(Loss) | true |
