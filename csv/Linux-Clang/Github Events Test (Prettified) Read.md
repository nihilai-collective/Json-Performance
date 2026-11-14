
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1472.99 | 0.0831576 | 4964.21ms | 65103 | 320 | 393151 | 42150.5 | 0.015631 | 3.49324 | 12.0117 | 2.32166 | 0.0111118 | 3.52806e-05 | 2.39524e-05 | 1(Win) | true |
| simdjson (ondemand) | 1222.33 | 0.0434016 | 5835.02ms | 65103 | 1280 | 622086 | 50794.2 | 0.0298773 | 4.20907 | 15.6129 | 2.86082 | 0.0157889 | 8.68216e-05 | 5.96411e-05 | 2(Loss) | true |
