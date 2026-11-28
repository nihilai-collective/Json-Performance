
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1051.24 | 0.213295 | 488.285ms | 4215 | 4890 | 325283 | 3823.8 | 0.166875 | 2.33747 | 1(Win) | true |
| Glaze | 802.343 | 0.336319 | 604.838ms | 4215 | 30 | 8517.24 | 5010 | 0.199203 | 3.06571 | 2(Loss) | true |
| simdjson (ondemand) | 545.419 | 0.115463 | 869.48ms | 4215 | 30 | 2172.41 | 7370 | 0.135501 | 4.528 | 3(Loss) | true |
