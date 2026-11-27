
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1323.73 | 0.458497 | 3886.77ms | 53331 | 40 | 1.24135e+06 | 38422 | 0.404031 | 1.86908 | 1(Win) | true |
| simdjson (ondemand) | 1097.03 | 0.0511433 | 4703.45ms | 53331 | 4890 | 2.7492e+06 | 46361.8 | 0.0292047 | 2.25556 | 2(Loss) | true |
