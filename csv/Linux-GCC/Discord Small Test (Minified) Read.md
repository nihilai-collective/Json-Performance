
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1623.48 | 0.077457 | 1010.37ms | 4857 | 320 | 1562.84 | 2853.13 | 0.0112827 | 3.21772 | 12.8359 | 2.47725 | 0.000921994 | 9.20064e-05 | 5.79061e-05 | 1(Win) | true |
| simdjson (ondemand) | 1384.08 | 0.0541707 | 1064.77ms | 4857 | 4890 | 16071.2 | 3346.61 | 0.0570869 | 3.71714 | 14.5324 | 2.59728 | 0.00192234 | 0.000113723 | 5.37668e-05 | 2(Loss) | true |
