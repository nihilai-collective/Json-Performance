
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.708 | 0.269388 | 665.83ms | 4215 | 160 | 35331.8 | 5516.25 | 0.523918 | 4.15411 | 1(Win) | true |
| simdjson (ondemand) | 664.054 | 0.20553 | 717.332ms | 4215 | 30 | 4643.68 | 6053.33 | 0.110011 | 4.55212 | 2(Loss) | true |
