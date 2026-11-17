
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1446.84 | 0.0618448 | 3856.48ms | 56369 | 2560 | 1.35172e+06 | 37155.2 | 0.332773 | 1.70997 | 1(Win) | true |
| simdjson (ondemand) | 1339.09 | 0.0820913 | 4045.86ms | 56369 | 2560 | 2.78034e+06 | 40145.1 | 0.382271 | 1.84763 | 2(Loss) | true |
