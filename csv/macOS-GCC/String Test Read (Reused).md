
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 989.416 | 0.484731 | 1214.45ms | 9578 | 160 | 320415 | 9232 | 0.65427 | 1(Win) | true |
| simdjson (ondemand) | 889.565 | 0.241066 | 1285.27ms | 9578 | 4890 | 2.99624e+06 | 10268.3 | 2.19019 | 2(Loss) | true |
