
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18756.3 | 0.264472 | 2350.5ms | 461466 | 2560 | 9.85787e+06 | 23463.4 | 0.223916 | 0.131839 | 1(Win) | true |
| simdjson (stage-1) | 16231 | 0.151976 | 2717.3ms | 461466 | 4890 | 8.30326e+06 | 27114 | 0.204146 | 0.15235 | 2(Loss) | true |
