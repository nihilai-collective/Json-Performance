
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 641.692 | 0.592288 | 148.355ms | 905 | 40 | 2538.46 | 1345 | 0.123762 | 3.79003 | 1(Win) | true |
| Glaze | 608.871 | 0.429231 | 152.134ms | 905 | 40 | 1480.77 | 1417.5 | 0.0588235 | 3.99829 | 2(Loss) | true |
| simdjson (ondemand) | 164.67 | 0.105674 | 542.156ms | 905 | 80 | 2454.11 | 5241.25 | 0.023855 | 14.9434 | 3(Loss) | true |
