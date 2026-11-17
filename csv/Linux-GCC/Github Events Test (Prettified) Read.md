
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1360.92 | 0.325412 | 4576ms | 65103 | 80 | 1.76317e+06 | 45621.4 | 0.0267347 | 1.81812 | 1(Win) | true |
| simdjson (ondemand) | 1187.43 | 0.0656228 | 5204.5ms | 65103 | 4890 | 5.75711e+06 | 52287 | 0.272484 | 2.08385 | 2(Loss) | true |
