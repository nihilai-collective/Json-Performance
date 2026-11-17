
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1556.08 | 0.05663 | 713.49ms | 9578 | 30 | 331.513 | 5870.07 | 0.136665 | 1.58339 | 1(Win) | true |
| Jsonifier (generic) | 841.271 | 0.551332 | 1223.99ms | 9578 | 40 | 143339 | 10857.7 | 1.06195 | 2.93531 | 2(Loss) | true |
