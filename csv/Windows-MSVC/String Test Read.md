
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4924.15 | 0.429449 | 190.801ms | 9578 | 40 | 2538.46 | 1855 | 0.0897666 | 0.494451 | 1(Win) | true |
| simdjson (stage-1) | 1498.65 | 0.0572586 | 619.947ms | 9578 | 40 | 487.179 | 6095 | 0.0821018 | 1.63939 | 2(Loss) | true |
