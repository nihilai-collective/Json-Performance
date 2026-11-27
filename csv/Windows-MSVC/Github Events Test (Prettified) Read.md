
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 896.237 | 0.195004 | 7089.53ms | 65103 | 4890 | 8.92384e+07 | 69275.3 | 0.132808 | 2.76126 | 1(Win) | true |
| simdjson (ondemand) | 751.62 | 0.195902 | 8554.34ms | 65103 | 4890 | 1.28054e+08 | 82604.3 | 0.870441 | 3.29275 | 2(Loss) | true |
