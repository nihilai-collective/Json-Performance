
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1844.05 | 0.130169 | 8969.26ms | 676745 | 80 | 1.6604e+07 | 349988 | 0.0672641 | 1.34242 | 1(Win) | true |
| simdjson (ondemand) | 1817.09 | 0.247005 | 9523.11ms | 676745 | 40 | 3.07871e+07 | 355181 | 0.289123 | 1.36234 | 2(Loss) | true |
