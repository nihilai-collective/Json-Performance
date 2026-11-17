
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.46 | 0.0992588 | 1656.46ms | 25388 | 40 | 3361.77 | 9236.02 | 0.0678944 | 1.97394 | 9.10672 | 1.60107 | 0.00283008 | 1.67402e-05 | 1.18166e-05 | 1(Win) | true |
| simdjson (ondemand) | 2176.5 | 0.198982 | 1844.84ms | 25388 | 80 | 39197.6 | 11124.2 | 0.0406604 | 2.37234 | 9.86019 | 1.7398 | 0.00388422 | 1.08319e-05 | 1.47708e-06 | 2(Loss) | true |
