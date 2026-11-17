
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2072.2 | 0.0646725 | 4601.29ms | 83958 | 320 | 199826 | 38639.4 | 0.119053 | 2.47377 | 10.6036 | 2.00465 | 0.00443231 | 3.05957e-05 | 2.06949e-05 | 1(Win) | true |
| simdjson (ondemand) | 1808.23 | 0.0431794 | 5166.83ms | 83958 | 320 | 116982 | 44280 | 0.0467839 | 2.84937 | 11.0492 | 1.8967 | 0.00974736 | 1.20596e-05 | 5.50871e-06 | 2(Loss) | true |
