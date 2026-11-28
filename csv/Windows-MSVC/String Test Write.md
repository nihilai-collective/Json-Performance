
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 525.818 | 0.20281 | 782.714ms | 4215 | 4890 | 1.17547e+06 | 7644.72 | 0.0853709 | 4.69174 | 1(Win) | true |
| Glaze | 416.409 | 0.184063 | 1142.51ms | 4215 | 30 | 9471.26 | 9653.33 | 0.0345185 | 5.92662 | 2(Loss) | true |
