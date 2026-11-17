
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.96 | 0.0564219 | 4862.82ms | 65103 | 640 | 348609 | 41364.8 | 0.0315839 | 3.43212 | 11.8587 | 2.28739 | 0.0103432 | 4.14487e-05 | 1.36082e-05 | 1(Win) | true |
| simdjson (ondemand) | 1253.83 | 0.0225225 | 5681.79ms | 65103 | 4890 | 608231 | 49518 | 0.13252 | 4.10132 | 14.7615 | 2.85616 | 0.0164571 | 4.25345e-05 | 2.08102e-05 | 2(Loss) | true |
