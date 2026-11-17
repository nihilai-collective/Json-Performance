
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 690.108 | 0.118855 | 1586.03ms | 9578 | 4890 | 1.2102e+06 | 13236 | 0.363859 | 3.58049 | 1(Win) | true |
| simdjson (ondemand) | 684.065 | 0.215625 | 1612.14ms | 9578 | 1280 | 1.06112e+06 | 13353 | 0.0526291 | 3.6125 | 2(Loss) | true |
