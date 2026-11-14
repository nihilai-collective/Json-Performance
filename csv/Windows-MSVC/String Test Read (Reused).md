
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1123.53 | 0.460228 | 1043.15ms | 9578 | 40 | 56000 | 8130 | 0.326931 | 2.69709 | 1(Win) | true |
| simdjson (ondemand) | 1067.54 | 0.573906 | 1063.76ms | 9578 | 640 | 1.54328e+06 | 8556.41 | 0.118557 | 2.83893 | 2(Loss) | true |
