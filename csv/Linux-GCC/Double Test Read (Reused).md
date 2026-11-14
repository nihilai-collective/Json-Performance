
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 414.28 | 0.0418627 | 423.009ms | 1811 | 30 | 91.3747 | 4168.93 | 0.0159939 | 5.93838 | 1(Win) | true |
| simdjson (ondemand) | 249.665 | 0.0615497 | 842.861ms | 1811 | 30 | 543.872 | 6917.7 | 0.164524 | 9.8769 | 2(Loss) | true |
