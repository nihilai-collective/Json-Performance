
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1996.3 | 0.067335 | 4752.96ms | 83958 | 2560 | 1.86722e+06 | 40108.6 | 0.0429197 | 2.54652 | 10.8943 | 2.00097 | 0.00447569 | 2.76505e-05 | 1.63447e-05 | 1(Win) | true |
| simdjson (ondemand) | 1740.57 | 0.109087 | 5317.88ms | 83958 | 4890 | 1.2314e+07 | 46001.3 | 0.0103983 | 2.90776 | 11.7957 | 1.9253 | 0.00781031 | 6.59181e-05 | 2.54923e-05 | 2(Loss) | true |
