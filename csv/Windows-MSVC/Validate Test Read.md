
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3269.01 | 0.237796 | 9523.77ms | 631514 | 160 | 3.07087e+07 | 184232 | 0.163926 | 0.757238 | 1(Win) | true |
| Glaze | 2591.82 | 0.0990476 | 6083.55ms | 631514 | 640 | 3.39019e+07 | 232369 | 0.556808 | 0.955121 | 2(Loss) | true |
