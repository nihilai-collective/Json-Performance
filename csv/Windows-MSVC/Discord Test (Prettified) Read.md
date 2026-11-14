
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1573.57 | 0.0472258 | 5081.45ms | 83958 | 1280 | 739126 | 50883.3 | 0.0218071 | 1.93061 | 1(Win) | true |
| Glaze | 1470.85 | 0.0434141 | 5460.2ms | 83958 | 2560 | 1.42985e+06 | 54437 | 0.123199 | 2.06532 | 2(Loss) | true |
| Jsonifier | 1439.82 | 0.0523667 | 5555.77ms | 83958 | 1280 | 1.0855e+06 | 55610.2 | 0.210707 | 2.11001 | 3(Loss) | true |
| simdjson (ondemand) | 1114.85 | 0.0422732 | 7181.37ms | 83958 | 4890 | 4.50746e+06 | 71820.2 | 0.102777 | 2.72521 | 4(Loss) | true |
