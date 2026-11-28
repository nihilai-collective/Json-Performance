
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 308.173 | 0.0575051 | 382.271ms | 1213 | 80 | 372.766 | 3753.76 | 0.0502576 | 7.97518 | 1(Win) | true |
| Glaze | 252.066 | 0.334205 | 475.238ms | 1213 | 30 | 7057.32 | 4589.3 | 0.012346 | 9.76263 | 2(Loss) | true |
