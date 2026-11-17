
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1924.55 | 0.113249 | 4181.13ms | 83958 | 4890 | 1.08554e+07 | 41603.7 | 0.464649 | 1.2856 | 1(Win) | true |
| simdjson (ondemand) | 1795.3 | 0.220321 | 4573.61ms | 83958 | 160 | 1.54483e+06 | 44598.9 | 0.378295 | 1.37822 | 2(Loss) | true |
