
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 317.613 | 0.24594 | 373.727ms | 1213 | 4890 | 392365 | 3642.19 | 0.0255762 | 7.73647 | 1(Win) | true |
| simdjson (reflection) | 312.739 | 0.0733926 | 380.72ms | 1213 | 80 | 589.592 | 3698.95 | 0.159251 | 7.85783 | 2(Loss) | true |
| Glaze | 284.963 | 0.0622598 | 425.808ms | 1213 | 30 | 191.638 | 4059.5 | 0.247769 | 8.62874 | 3(Loss) | true |
