
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7948.35 | 0.0360986 | 118.856ms | 9578 | 160 | 27.5358 | 1149.21 | 0.0963548 | 0.304191 | 1(Win) | true |
| simdjson (stage-1) | 3259.3 | 0.0836508 | 284.855ms | 9578 | 30 | 164.878 | 2802.53 | 0.0689376 | 0.752377 | 2(Loss) | true |
