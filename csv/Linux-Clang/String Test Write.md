
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1653.08 | 0.120798 | 233.947ms | 4215 | 30 | 258.851 | 2431.67 | 0.0424768 | 1.48084 | 1(Win) | true |
| Glaze | 925.983 | 0.0708621 | 448.277ms | 4215 | 40 | 378.51 | 4341.05 | 0.325662 | 2.65855 | 2(Loss) | true |
