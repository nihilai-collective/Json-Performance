
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1736.77 | 0.0690036 | 730.513ms | 9578 | 4890 | 64405 | 5259.37 | 0.129237 | 1.74113 | 1(Win) | true |
| Glaze | 1245.47 | 0.0751286 | 954.51ms | 9578 | 2560 | 77720.4 | 7334.02 | 0.234335 | 2.4319 | 2(Loss) | true |
| Jsonifier (two-stage) | 1175.39 | 0.0771094 | 991.613ms | 9578 | 2560 | 91926.4 | 7771.29 | 0.132372 | 2.57581 | 3(Loss) | true |
| simdjson (ondemand) | 1081.03 | 0.0710219 | 1059.36ms | 9578 | 4890 | 176102 | 8449.59 | 0.0219407 | 2.80395 | 4(Loss) | true |
