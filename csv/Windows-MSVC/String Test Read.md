
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3360.28 | 0.255552 | 139.055ms | 4215 | 160 | 1495.28 | 1196.25 | 0.52521 | 0.882782 | 1(Win) | true |
| simdjson (stage-1) | 1522.63 | 0.297146 | 276.341ms | 4215 | 40 | 2461.54 | 2640 | 0.253165 | 1.97565 | 2(Loss) | true |
