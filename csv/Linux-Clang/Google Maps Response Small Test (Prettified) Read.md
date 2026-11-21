
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3510.31 | 0.0871857 | 257.433ms | 9378 | 30 | 148.028 | 2547.8 | 0.0797438 | 0.698457 | 1(Win) | true |
| Jsonifier | 3136.1 | 0.0450298 | 295.911ms | 9378 | 80 | 131.926 | 2851.81 | 0.0802765 | 0.782403 | 2(Loss) | true |
| Glaze | 2533.17 | 0.0635361 | 353.484ms | 9378 | 40 | 201.276 | 3530.57 | 0.0497782 | 0.96993 | 3(Loss) | true |
| simdjson (ondemand) | 2095.34 | 0.107375 | 431.256ms | 9378 | 80 | 1680.39 | 4268.3 | 0.0726812 | 1.1746 | 4(Loss) | true |
