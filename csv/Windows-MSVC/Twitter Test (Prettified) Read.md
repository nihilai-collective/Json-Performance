
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14897.6 | 0.263586 | 4304.15ms | 631514 | 30 | 340644 | 40426.7 | 1.4144 | 0.203777 | 1(Win) | true |
| simdjson (stage-1) | 12003.6 | 0.698851 | 5046.25ms | 631514 | 2560 | 3.14741e+08 | 50173.2 | 0.66103 | 0.252974 | 2(Loss) | true |
