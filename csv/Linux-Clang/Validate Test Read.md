
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3791.58 | 0.274332 | 8199.46ms | 631514 | 640 | 1.21523e+08 | 158841 | 0.0976054 | 0.652855 | 1(Win) | true |
| Glaze | 2377.43 | 0.203721 | 6514.38ms | 631514 | 160 | 4.26131e+07 | 253323 | 0.478838 | 1.04127 | 2(Loss) | true |
