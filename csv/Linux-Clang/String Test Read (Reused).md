
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1533.69 | 0.0545691 | 740.448ms | 9578 | 40 | 422.5 | 5955.75 | 0.155071 | 1.6064 | 1(Win) | true |
| Jsonifier (generic) | 784.24 | 0.0818892 | 1308.28ms | 9578 | 4890 | 444850 | 11647.3 | 0.0356214 | 3.14933 | 2(Loss) | true |
