
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3413.39 | 0.0357097 | 3083.17ms | 83958 | 640 | 44906.1 | 23457.2 | 0.0196673 | 1.51039 | 7.03511 | 1.1654 | 0.00221149 | 9.60302e-06 | 5.47149e-06 | 1(Win) | true |
| simdjson (ondemand) | 3121.27 | 0.0726267 | 3322.56ms | 83958 | 320 | 111072 | 25652.5 | 0.00862413 | 1.64853 | 7.2875 | 1.15903 | 0.0024947 | 3.49877e-06 | 1.11663e-06 | 2(Loss) | true |
