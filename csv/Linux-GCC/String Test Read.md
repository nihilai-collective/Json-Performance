
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 753.31 | 0.0390353 | 543.004ms | 4215 | 30 | 130.162 | 5336.1 | 0.048701 | 3.27008 | 1(Win) | true |
| simdjson (ondemand) | 709.625 | 0.264028 | 552.193ms | 4215 | 1280 | 286319 | 5664.6 | 0.125539 | 3.47223 | 2(Loss) | true |
