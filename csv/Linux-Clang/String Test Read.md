
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 810.605 | 0.119304 | 499.663ms | 4215 | 4890 | 171156 | 4958.93 | 0.0618934 | 3.03849 | 1(Win) | true |
| Jsonifier (generic) | 688.175 | 0.182555 | 591.977ms | 4215 | 2560 | 291090 | 5841.16 | 0.378964 | 3.58082 | 2(Loss) | true |
