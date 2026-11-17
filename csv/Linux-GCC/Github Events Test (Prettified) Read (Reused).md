
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.07 | 0.0224595 | 4664.51ms | 65103 | 4890 | 285153 | 34000.4 | 0.0338599 | 2.81391 | 10.0714 | 1.88073 | 0.00812704 | 1.7801e-05 | 9.51772e-06 | 1(Win) | true |
| simdjson (ondemand) | 1489.84 | 0.0478015 | 5464.95ms | 65103 | 1280 | 507945 | 41673.7 | 0.0346092 | 3.45539 | 13.0161 | 2.46108 | 0.0135015 | 2.95205e-05 | 1.48923e-05 | 2(Loss) | true |
