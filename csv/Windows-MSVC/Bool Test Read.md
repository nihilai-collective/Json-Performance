
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1435.47 | 0.2079 | 64.0874ms | 905 | 80 | 125 | 601.25 | 0.208333 | 1.63145 | 1(Win) | true |
| simdjson (stage-1) | 589.13 | 0.366302 | 186.088ms | 905 | 80 | 2303.8 | 1465 | 0.170358 | 4.13517 | 2(Loss) | true |
